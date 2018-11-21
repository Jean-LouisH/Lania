#include "Lania.hpp"
#include "Configuration.hpp"
#include "Core.hpp"
#include "Input.hpp"
#include "OS/File.hpp"
#include "OS/OS.hpp"
#include "OS/Logging.hpp"
#include "GL/glew.h"
#include <Constants.hpp>
#include "SDL.h"
#include <SDL_image.h>
#include <Core/DataStructures/String.hpp>
#include <Core/DataStructures/List.hpp>
#include <Rendering/RenderingSDL.hpp>
#include <Physics/Physics2D.hpp>
#include <Audio/AudioSDL.hpp>
#include <sstream>
#include <TemporarySceneTesting.hpp>

void Lania::initialize(Core* core)
{
	//Development Test 
	String initFilePath = "../Demos/PhysicsTest/Init.cfg";

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
		IMG_Init(IMG_INIT_JPG);

		Mix_Init(MIX_INIT_OGG);
		Mix_OpenAudio(44100, AUDIO_S16SYS, 2, pow(2, 11));

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
				core->platform.renderingAPIVersion = "Vulkan";
			}
			else
			{
				Log::toConsole("Rendering Engine: SDL");
				core->SDLRenderer = SDL_CreateRenderer(
					core->window,
					-1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				SDL_RendererInfo SDLRendererInfo;
				SDL_GetRendererInfo(core->SDLRenderer, &SDLRendererInfo);
				core->platform.renderingAPIVersion = (char*)SDLRendererInfo.name;
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

	application->scene.SDLRendererCopy = core->SDLRenderer;
	application->scene.windowCopy.height = core->appConfig.windowHeight_px;
	application->scene.windowCopy.width = core->appConfig.windowWidth_px;

	testLoadEntityComponentSystem(application, core);

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
				(core->timer.process.delta_ns / NS_IN_MS);
		}
		else
		{
			delay = (MS_IN_S / UPDATES_PER_S) -
				(core->timer.process.delta_ns / NS_IN_MS);
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
		if (time->FPS.delta_ns / NS_IN_MS >= MS_IN_S)
		{
			core->FPS = (passedFrames / (time->FPS.delta_ns / NS_IN_S));
			time->FPS.setStart();
			passedFrames = 1;

			String rendererString;
			switch (core->renderer)
			{
				case SDL_RENDERER: rendererString = "SDL"; break;
				case LANIA_OPENGL_RENDERER:
				case LANIA_VULKAN_RENDERER: rendererString = "Lania"; break;
			}

			String FPSString = std::to_string(core->FPS);
			String frameUtilizationString = 
				std::to_string((int)(((double)time->process.delta_ns / (double)time->frame.delta_ns) * 100));
			String batteryString = std::to_string(core->platform.batteryLife_pct);
			SDL_SetWindowTitle(core->window,
				(core->appConfig.appName + " - Lania Debug ->" + 
					" Renderer: " + rendererString + 
					", API: " + core->platform.renderingAPIVersion + 
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

	//Testing

	if (core->input.pressedKeys.count(SDLK_a))
		application->scene.subscenes2D.at(0).activeRigidBodies.at(0).velocity_px_per_s.x = -500;

	if (core->input.pressedKeys.count(SDLK_d))
		application->scene.subscenes2D.at(0).activeRigidBodies.at(0).velocity_px_per_s.x = 500;

	if (core->input.releasedKeys.count(SDLK_k))
		core->output.immediateSounds.push(application->scene.subscenes2D.at(0).entities.at(4).audioSources.at(0));

	if (core->input.releasedKeys.count(SDLK_r))
		core->state = RESTARTING;

	if (core->input.releasedKeys.count(SDLK_y))
		OS::toggleWindowedFullscreen(core->window, &core->state);

	if (core->input.releasedKeys.count(SDLK_u))
		OS::setToFullscreen(core->window, &core->platform.SDLDisplayMode, &core->state);

	if (core->input.releasedKeys.count(SDLK_i))
		OS::setToWindowed(core->window, &core->appConfig, &core->state);

	//////////////////////////

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
			//Physics2D::gravitate(rigidBodies, rigidBodyCount);
			Physics2D::displace(entities, rigidBodies, rigidBodyCount);
			Physics2D::lock(entities, pointLocks, pointLockCount);
		}

		time->simulation_ms += MS_PER_UPDATE;
		time->lag_ms -= MS_PER_UPDATE;
	}

	Rendering2D::SDL::buildRenderablesFromSprites(
		&core->output.SDLRenderables,
		&application->scene.subscenes2D,
		core->window
	);

	time->lag_ms += time->frame.delta_ns / NS_IN_MS;

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
	else if (core->renderer == SDL_RENDERER)
	{
		SDL_SetRenderDrawColor(core->SDLRenderer, 0, 0, 0, 255);
		SDL_RenderClear(core->SDLRenderer);

		int renderableCount = core->output.SDLRenderables.size();
		SDLRenderable* renderables = core->output.SDLRenderables.data();
		for (int i = 0; i < renderableCount; i++)
			SDL_RenderCopyEx(
				core->SDLRenderer,
				renderables[i].texture,
				&renderables[i].textureRect,
				&renderables[i].renderingRect,
				renderables[i].rotation,
				NULL,
				renderables[i].flip);

		SDL_RenderPresent(core->SDLRenderer);
	}

	Audio::SDL::playSounds(&core->output.immediateSounds, &core->output.scheduledSounds);
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
	else if (core->renderer == SDL_RENDERER)
		SDL_DestroyRenderer(core->SDLRenderer);
	SDL_DestroyWindow(core->window);
	SDL_Quit();
}
