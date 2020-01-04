#include <Lania.hpp>
#include <Application/ApplicationBooting.hpp>
#include <Editor/EditorBooting.hpp>
#include <Core/Core.hpp>
#include <Core/HAL/Input.hpp>
#include <Core/HAL/OS.hpp>
#include <Core/HAL/Logging.hpp>
#include <Utilities/Definitions/Constants.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <GL/glew.h>
#include <Utilities/GenericCollections/String.hpp>
#include <Utilities/GenericCollections/List.hpp>
#include <Engines/Physics/Physics2D.hpp>
#include <Core/HAL/FileSystem.hpp>
#include <Core/HAL/EngineTimers.hpp>
#include <Application/Scene/2D/Scene2D.hpp>
#include <Engines/Physics/Physics.hpp>
#include <Engines/Rendering/Rendering.hpp>

void Lania::initialize(Core* core)
{
	String exportFilePath = "";
#if _DEBUG
	exportFilePath += DEFAULT_DEBUG_EXPORT_PATH;
#endif
	unsigned char* state = &core->state;
	BootConfiguration* bootConfig = &core->bootConfig;
	Platform* platform = &core->platform;

	Log::toConsole("Initializing Core...\n");
	core->engineTimers.run.setStart();
	core->executableName = FileSystem::getExecutableName(core->filepath);
	bootConfig->dataDirectoryPath = exportFilePath + core->executableName + "_Data/";

	if (FileSystem::exists(bootConfig->dataDirectoryPath + "Application_Boot.yml"))
		ApplicationBooting::build(bootConfig);
	else
		EditorBooting::build(bootConfig);

	SDL_GameControllerAddMappingsFromFile((exportFilePath + core->executableName +
		"_Data/" + "gamecontrollerdb.txt").c_str());
	platform->logicalCoreCount = SDL_GetCPUCount();
	platform->L1CacheLineSize_B = SDL_GetCPUCacheLineSize();
	platform->systemRAM_MB = SDL_GetSystemRAM();
	platform->OS = (char*)SDL_GetPlatform();
	SDL_GetPowerInfo(NULL, &platform->batteryLife_pct);
	*state = Core::states::INITIALIZING;

	Log::toConsole("Executable Name: " + core->executableName + ".exe");
	Log::toConsole("Logical Cores: " + std::to_string(platform->logicalCoreCount));
	Log::toConsole("L1 Cache Line Size: " + std::to_string(platform->L1CacheLineSize_B) + " B");
	Log::toConsole("System RAM Size: " + std::to_string(platform->systemRAM_MB) + " MB");

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log(
			"SDL could not initialize because: %s",
			SDL_GetError);
		*state = Core::states::SHUTDOWN;
	}
	else
	{
		SDL_GetDesktopDisplayMode(0, &platform->SDLDisplayMode);
		Log::toConsole("Target FPS: " + std::to_string(bootConfig->targetFPS));
		IMG_Init(IMG_INIT_PNG);

		if (bootConfig->renderingAPI == "sdl_2")
		{

		}
		else if (bootConfig->renderingAPI == "opengl_3_3")
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

		core->window = SDL_CreateWindow(
			bootConfig->windowTitle.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			bootConfig->windowWidth_px,
			bootConfig->windowHeight_px,
			bootConfig->windowFlags);

		if (core->window == NULL)
		{
			SDL_Log(
				"SDL could not create the window because: %s",
				SDL_GetError());
			*state = Core::states::SHUTDOWN;
		}
		else
		{
			SDL_Surface* logo = IMG_Load((bootConfig->dataDirectoryPath + bootConfig->icon).c_str());
			SDL_SetWindowIcon(core->window, logo);
			SDL_FreeSurface(logo);

			SDL_DisableScreenSaver();
			SDL_GetCurrentDisplayMode(0, &platform->SDLDisplayMode);

			if (bootConfig->renderingAPI == "sdl_2")
			{
				SDL_RendererInfo sdlRendererInfo;

				core->renderer = Core::renderers::LANIA_SDL_2_RENDERER;
				core->sdlRenderer = SDL_CreateRenderer(
					core->window, 
					-1, 
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				SDL_GetRendererInfo(core->sdlRenderer, &sdlRendererInfo);
				core->platform.renderingAPIVersion = (char*)sdlRendererInfo.name;

				Log::toConsole("Rendering Engine: Lania SDL 2");
			}
			else if (bootConfig->renderingAPI == "opengl_3_3")
			{
				core->renderer = Core::renderers::LANIA_OPENGL_3_3_RENDERER;
				core->glContext = SDL_GL_CreateContext(core->window);

				if (glewInit() != GLEW_OK)
				{
					Log::toConsole("GLEW failed to initialize.");
					*state = Core::states::SHUTDOWN;
				}
				else
				{
					String* renderingAPIString = new String;
					*renderingAPIString += "OpenGL ";
					*renderingAPIString += (char*)glGetString(GL_VERSION);
					core->platform.renderingAPIVersion = (char*)renderingAPIString->c_str();

					glViewport(0, 0, bootConfig->windowWidth_px, bootConfig->windowHeight_px);
					Log::toConsole("Rendering Engine: Lania OpenGL 3.3");
				}
			}

			if (bootConfig->windowFlags & SDL_WINDOW_FULLSCREEN)
				*state = Core::states::RUNNING_APPLICATION_FULLSCREEN;
			else if (bootConfig->windowFlags & SDL_WINDOW_FULLSCREEN_DESKTOP)
				*state = Core::states::RUNNING_APPLICATION_FULLSCREEN_DESKTOP;
			else if (*state != Core::states::SHUTDOWN)
				*state = Core::states::RUNNING_APPLICATION_WINDOWED;

			Log::toConsole("Initialization complete.\n");
		}
	}
}

void Lania::loop(Core* core, Application* application)
{
	EngineTimers* engineTimers = &core->engineTimers;
	engineTimers->FPS.setStart();

	application->init();

	do
	{
		engineTimers->frame.setStart();
		engineTimers->process.setStart();

		Lania::input(core);
		Lania::logic(core, application);
		Lania::compute(core, application);
		Lania::output(core);

		engineTimers->process.setEnd();

		Lania::sleep(core);

		engineTimers->frame.setEnd();
		core->frameCount++;

		Lania::benchmark(core);

	} while (core->state != Core::states::SHUTDOWN && 
		core->state != Core::states::RESTARTING);
}

void Lania::sleep(Core* core)
{
	int delay = 0;
	
	core->engineTimers.sleep.setStart();

	if (core->bootConfig.targetFPS < COMPUTE_UPDATES_PER_S)
		delay = (MS_IN_S / core->bootConfig.targetFPS) -
			(core->engineTimers.process.getDelta_ns() / NS_IN_MS);
	else
		delay = (MS_IN_S / COMPUTE_UPDATES_PER_S) -
			(core->engineTimers.process.getDelta_ns() / NS_IN_MS);

	if (delay > 0)
		SDL_Delay(delay);

	core->engineTimers.sleep.setEnd();
}

void Lania::benchmark(Core* core)
{
	static int passedFrames;
	EngineTimers* engineTimers = &core->engineTimers;
	engineTimers->benchmark.setStart();
	passedFrames++;
	engineTimers->FPS.setEnd();
#ifdef _DEBUG
	//Display FPS and other data to Window title.
	if (engineTimers->FPS.getDelta_ns() / NS_IN_MS >= MS_IN_S)
	{
		core->FPS = (passedFrames / (engineTimers->FPS.getDelta_ns() / NS_IN_S));
		engineTimers->FPS.setStart();
		passedFrames = 1;

		String rendererString = "Lania";

		String FPSString = std::to_string(core->FPS);
		String frameUtilizationString = 
			std::to_string((int)(((double)engineTimers->process.getDelta_ns() / (double)engineTimers->frame.getDelta_ns()) * 100));
		String batteryString = std::to_string(core->platform.batteryLife_pct);
		SDL_SetWindowTitle(core->window,
			(core->bootConfig.windowTitle + " ->" + 
				" Rendering API: " + core->platform.renderingAPIVersion + 
				", FPS: " + FPSString +
				", Frame Time Utilization: " + frameUtilizationString + "%" + 
				", Battery: " + batteryString + "%").c_str());
	}
#endif
	engineTimers->benchmark.setEnd();
}

void Lania::input(Lania::Core* core)
{
	core->engineTimers.input.setStart();

	if (SDL_NumJoysticks() != core->input.gameControllers.size())
		OS::detectGameControllers(&core->input);
	OS::detectBatteryLife(core);
	OS::pollInputEvents(core);

	core->engineTimers.input.setEnd();
}

void Lania::logic(Core* core, Application* application)
{
	core->engineTimers.logic.setStart();

	application->runCommandLine();
	application->interpretStartLogic();
	application->interpretInputLogic();
	application->interpretFrameLogic();

	core->engineTimers.logic.setEnd();
}

void Lania::compute(Core* core, Application* application)
{
	EngineTimers* engineTimers = &core->engineTimers;
	engineTimers->compute.setStart();
	List<Scene2D>* subScene2Ds = &application->scene.subScenes2D;
	int scene2DCount = subScene2Ds->size();

	while (engineTimers->lag_ms >= MS_PER_COMPUTE_UPDATE)
	{
		application->interpretComputeLogic(MS_PER_COMPUTE_UPDATE);
		Physics::compute(subScene2Ds, application->runtime_ms);
		application->runtime_ms += MS_PER_COMPUTE_UPDATE;
		engineTimers->lag_ms -= MS_PER_COMPUTE_UPDATE;
	}

	application->interpretLateLogic();
	application->interpretFinalLogic();
	application->buildRenderables();

	engineTimers->lag_ms += engineTimers->frame.getDelta_ns() / NS_IN_MS;

	engineTimers->compute.setEnd();
}

void Lania::output(Core* core)
{
	core->engineTimers.output.setStart();
	Rendering::render(&core->output.renderables, core->renderer, core->window, core->sdlRenderer);
	core->engineTimers.output.setEnd();
}

void Lania::shutdown(Core* core, Application* application)
{
	List<SDL_GameController*>* gameControllers = &core->input.gameControllers;
	List<SDL_Haptic*>* haptics = &core->input.haptics;

	core->engineTimers.shutdown.setStart();
	application->scene.deleteAssets();

	for (int i = 0; i < gameControllers->size(); ++i)
	{
		SDL_GameControllerClose(gameControllers->at(i));
		SDL_HapticClose(haptics->at(i));
	}

	gameControllers->clear();
	haptics->clear();

	IMG_Quit();
	if (core->renderer == Core::renderers::LANIA_OPENGL_3_3_RENDERER)
		SDL_GL_DeleteContext(core->glContext);
	SDL_DestroyWindow(core->window);
	SDL_Quit();
	core->engineTimers.shutdown.setEnd();
}
