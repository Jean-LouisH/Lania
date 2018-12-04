#include <Lania.hpp>
#include <Core/Configuration.hpp>
#include <Core/Core.hpp>
#include <Core/HAL/Input.hpp>
#include <Core/HAL/OS.hpp>
#include <Core/HAL/Logging.hpp>
#include <GL/glew.h>
#include <Utilities/Definitions/Constants.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <Utilities/DataStructures/String.hpp>
#include <Utilities/DataStructures/List.hpp>
#include <Engines/Physics/Physics2D.hpp>
#include <Core/HAL/File.hpp>
#include <Core/HAL/Timer.hpp>
#include <Application/Scene/2D/Scene2D.hpp>
#include <Engines/Physics/Physics2D.hpp>

void Lania::initialize(Core* core)
{
	//Development Test 
	String initFilePath = "../../Demos/PhysicsTest/Init.cfg";

	AppConfig* appConfig = &core->appConfig;
	unsigned char* state = &core->state;

	Log::toConsole("Initializing Core...\n");

	core->timer.run.setStart();
	core->executableName = File::getExecutableName(core->filepath);
	*appConfig = Config::parseInit(File::read(initFilePath));
	SDL_GameControllerAddMappingsFromFile("../Data/gamecontrollerdb.txt");
	core->platform.logicalCoreCount = SDL_GetCPUCount();
	core->platform.L1CacheSize_B = SDL_GetCPUCacheLineSize();
	core->platform.systemRAM_MB = SDL_GetSystemRAM();
	core->platform.OS = (char*)SDL_GetPlatform();
	SDL_GetPowerInfo(NULL, &core->platform.batteryLife_pct);
	*state = INITIALIZING;

	Log::toConsole("Executable Name: " + core->executableName + ".exe");
	Log::toConsole("Logical Cores: " + std::to_string(core->platform.logicalCoreCount));
	Log::toConsole("L1 Cache Size: " + std::to_string(core->platform.L1CacheSize_B) + " B");
	Log::toConsole("System RAM Size: " + std::to_string(core->platform.systemRAM_MB) + " MB");

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log(
			"SDL could not initialize because: %s",
			SDL_GetError);
		*state = SHUTDOWN;
	}
	else
	{
		//Development test
		SDL_GetDesktopDisplayMode(0, &core->platform.SDLDisplayMode);
		appConfig->targetFPS = 60;

		Log::toConsole("Target FPS: " + std::to_string(appConfig->targetFPS));

		IMG_Init(IMG_INIT_PNG);

		if (!(appConfig->windowFlags & SDL_WINDOW_OPENGL) &&
			!(appConfig->windowFlags & SDL_WINDOW_VULKAN))
		{
			appConfig->windowFlags |= SDL_WINDOW_OPENGL;
		}

		if (appConfig->windowFlags & SDL_WINDOW_OPENGL)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		}
		else if (appConfig->windowFlags & SDL_WINDOW_VULKAN)
		{
			;
		}

		core->window = SDL_CreateWindow(
			appConfig->appName.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			appConfig->windowWidth_px,
			appConfig->windowHeight_px,
			appConfig->windowFlags);

		if (core->window == NULL)
		{
			SDL_Log(
				"SDL could not create the window because: %s",
				SDL_GetError());
			*state = SHUTDOWN;
		}
		else
		{
			String rootPath = "";

#if _DEBUG
			//Development test
			rootPath += "../Demos/";
#endif
			String iconString = rootPath + appConfig->appName + "/Icon.png";
			SDL_Surface* logo = IMG_Load(iconString.c_str());
			SDL_SetWindowIcon(core->window, logo);
			SDL_FreeSurface(logo);

			SDL_DisableScreenSaver();
			SDL_GetCurrentDisplayMode(0, &core->platform.SDLDisplayMode);

			if (appConfig->windowFlags & SDL_WINDOW_OPENGL)
			{
				Log::toConsole("Rendering Engine: Lania OpenGL");
				core->renderer = LANIA_OPENGL_RENDERER;
				core->glContext = SDL_GL_CreateContext(core->window);
				glViewport(0, 0, appConfig->windowWidth_px, appConfig->windowHeight_px);

				if (glewInit() != GLEW_OK)
				{
					Log::toConsole("GLEW failed to initialize.");
					*state = SHUTDOWN;
				}
				else
				{
					String* renderingAPIString = new String;
					*renderingAPIString += "OpenGL ";
					*renderingAPIString += (char*)glGetString(GL_VERSION);
					core->platform.renderingAPIVersion = (char*)renderingAPIString->c_str();
				}
			}
			else if (appConfig->windowFlags & SDL_WINDOW_VULKAN)
			{
				Log::toConsole("Rendering Engine: Lania Vulkan");
				core->renderer = LANIA_VULKAN_RENDERER;
				core->platform.renderingAPIVersion = (char*)"Vulkan";
			}

			if (appConfig->windowFlags & SDL_WINDOW_FULLSCREEN)
				*state = RUNNING_APPLICATION_FULLSCREEN;
			else if (appConfig->windowFlags & SDL_WINDOW_FULLSCREEN_DESKTOP)
				*state = RUNNING_APPLICATION_FULLSCREEN_DESKTOP;
			else if (*state != SHUTDOWN)
				*state = RUNNING_APPLICATION_WINDOWED;

			Log::toConsole("Initialization complete.\n");
		}
	}
}

void Lania::loop(Core* core, Application* application)
{
	Timer* time = &core->timer;
	time->FPS.setStart();

	application->scene.windowCopy.height = core->appConfig.windowHeight_px;
	application->scene.windowCopy.width = core->appConfig.windowWidth_px;

	do
	{
		time->frame.setStart();
		time->process.setStart();

		Lania::input(core);
		Lania::logic(core, application);
		Lania::compute(core, application);
		Lania::output(core);

		time->process.setEnd();

		int delay = 0;
		
		if (core->appConfig.targetFPS < UPDATES_PER_S)
		{
			delay = (MS_IN_S / core->appConfig.targetFPS) -
				(core->timer.process.getDelta_ns() / NS_IN_MS);
		}
		else
		{
			delay = (MS_IN_S / UPDATES_PER_S) -
				(core->timer.process.getDelta_ns() / NS_IN_MS);
		}

		if (delay > 0)
			SDL_Delay(delay);

		time->frame.setEnd();
		core->frameCount++;

		static int passedFrames;
		passedFrames++;
		time->FPS.setEnd();
#ifdef _DEBUG
		//Display FPS and other data to Window title.
		if (time->FPS.getDelta_ns() / NS_IN_MS >= MS_IN_S)
		{
			core->FPS = (passedFrames / (time->FPS.getDelta_ns() / NS_IN_S));
			time->FPS.setStart();
			passedFrames = 1;

			String rendererString = "Lania";

			String FPSString = std::to_string(core->FPS);
			String frameUtilizationString = 
				std::to_string((int)(((double)time->process.getDelta_ns() / (double)time->frame.getDelta_ns()) * 100));
			String batteryString = std::to_string(core->platform.batteryLife_pct);
			SDL_SetWindowTitle(core->window,
				(core->appConfig.appName + " - Lania Debug ->" + 
					", Rendering API: " + core->platform.renderingAPIVersion + 
					", FPS: " + FPSString +
					", Frame Time Utilization: " + frameUtilizationString + "%" + 
					", Battery: " + batteryString + "%").c_str());
		}
#endif
	} while (core->state != SHUTDOWN && core->state != RESTARTING);
}

void Lania::input(Lania::Core* core)
{
	core->timer.input.setStart();

	if (SDL_NumJoysticks() != core->input.gameControllers.size())
		OS::detectGameControllers(&core->input);
	OS::detectBatteryLife(core);
	OS::pollInputEvents(core);

	core->timer.input.setEnd();
}

void Lania::logic(Core* core, Application* application)
{
	Timer* time = &core->timer;
	time->logic.setStart();

	time->logic.setEnd();
}

void Lania::compute(Core* core, Application* application)
{
	Timer* time = &core->timer;
	time->compute.setStart();

	List<Scene2D>* scene2Ds = &application->scene.subscenes2D;
	int scene2DCount = scene2Ds->size();

	while (time->lag_ms >= MS_PER_UPDATE)
	{
		for (int i = 0; i < scene2DCount; i++)
		{
			Scene2D* scene2D = &scene2Ds->at(i);
			Entity2D* entities = scene2D->entities.data();

			BoxCollider2D* boxColliders = scene2D->activeBoxColliders.data();
			RigidBody2D* rigidBodies = scene2D->activeRigidBodies.data();
			PointLock2D* pointLocks = scene2D->pointLocks.data();

			int boxColliderCount = scene2D->activeBoxColliders.size();
			int rigidBodyCount = scene2D->activeRigidBodies.size();
			int pointLockCount = scene2D->pointLocks.size();

			Physics2D::detectCollisions(
				time->simulation_ms,
				&scene2D->dynamicCollisionEvents, 
				&scene2D->staticCollisionEvents, 
				entities, 
				rigidBodies, 
				rigidBodyCount, 
				boxColliders, 
				boxColliderCount);

			DynamicCollisionEvent2D* dynamicCollisionEvents = scene2D->dynamicCollisionEvents.data();
			int DynamicCollisionEventCount = scene2D->dynamicCollisionEvents.size();

			Physics2D::handleCollisions(dynamicCollisionEvents, DynamicCollisionEventCount, rigidBodies);
			Physics2D::decelerate(rigidBodies, rigidBodyCount);
			Physics2D::gravitate(rigidBodies, rigidBodyCount);
			Physics2D::displace(entities, rigidBodies, rigidBodyCount);
			Physics2D::lock(entities, pointLocks, pointLockCount);
		}

		time->simulation_ms += MS_PER_UPDATE;
		time->lag_ms -= MS_PER_UPDATE;
	}

	time->lag_ms += time->frame.getDelta_ns() / NS_IN_MS;

	time->compute.setEnd();
}

void Lania::output(Core* core)
{
	Timer* time = &core->timer;
	time->output.setStart();
	if (core->renderer == LANIA_OPENGL_RENDERER)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SDL_GL_SwapWindow(core->window);
	}
	else if (core->renderer == LANIA_VULKAN_RENDERER)
	{
		;
	}

	time->output.setEnd();
}

void Lania::shutdown(Core* core, Application* application)
{
	List<SDL_GameController*>* gameControllers = &core->input.gameControllers;
	List<SDL_Haptic*>* haptics = &core->input.haptics;

	application->scene.deleteAssets();

	for (int i = 0; i < gameControllers->size(); ++i)
	{
		SDL_GameControllerClose(gameControllers->at(i));
		SDL_HapticClose(haptics->at(i));
	}

	gameControllers->clear();
	haptics->clear();

	if (core->renderer == LANIA_OPENGL_RENDERER)
		SDL_GL_DeleteContext(core->glContext);
	SDL_DestroyWindow(core->window);
	SDL_Quit();
}
