#include "LaniaEngine.hpp"
#include "Configuration.hpp"
#include "Engine.hpp"
#include "Input.hpp"
#include "OS/File.hpp"
#include "OS/OS.hpp"
#include "GL/glew.h"
#include <Constants.hpp>
#include "SDL.h"
#include <SDL_image.h>
#include <Core/DataStructures/String.hpp>
#include <Core/DataStructures/List.hpp>
#include <Rendering/RendererSDL.hpp>
#include <sstream>

void Lania::initialize(Engine* engine)
{
	//Development Test 
	String initFilePath = "../Demos/SpriteTest/Init.cfg";

	AppConfig* appConfig = &engine->appConfig;
	unsigned char* state = &engine->state;

	engine->timer.run.setStart();
	engine->filepath = SDL_GetBasePath();
	*appConfig = Config::parseInit(File::read(initFilePath));
	SDL_GameControllerAddMappingsFromFile("../Data/gamecontrollerdb.txt");
	engine->platform.logicalCoreCount = SDL_GetCPUCount();
	engine->platform.L1CacheSize_B = SDL_GetCPUCacheLineSize();
	engine->platform.systemRAM_MB = SDL_GetSystemRAM();
	engine->platform.OS = (char*)SDL_GetPlatform();
	SDL_GetPowerInfo(NULL, &engine->platform.batteryLife_pct);
	*state = RUNNING_APPLICATION;

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
		appConfig->targetFPS = 60;
		IMG_Init(IMG_INIT_PNG);

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

		engine->window = SDL_CreateWindow(
			appConfig->appName.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			appConfig->windowWidth_px,
			appConfig->windowHeight_px,
			appConfig->windowFlags);

		if (engine->window == NULL)
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
			SDL_SetWindowIcon(engine->window, logo);
			SDL_FreeSurface(logo);

			SDL_DisableScreenSaver();
			SDL_GetCurrentDisplayMode(0, &engine->platform.SDLDisplayMode);

			if (appConfig->windowFlags & SDL_WINDOW_OPENGL)
			{
				engine->renderer = LANIA_OPENGL_RENDERER;
				engine->glContext = SDL_GL_CreateContext(engine->window);
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
					engine->platform.renderingAPIVersion = (char*)renderingAPIString->c_str();
				}
			}
			else if (appConfig->windowFlags & SDL_WINDOW_VULKAN)
			{
				engine->renderer = LANIA_VULKAN_RENDERER;
				engine->platform.renderingAPIVersion = "Vulkan";
			}
			else
			{
				engine->SDLRenderer = SDL_CreateRenderer(
					engine->window,
					-1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				SDL_RendererInfo SDLRendererInfo;
				SDL_GetRendererInfo(engine->SDLRenderer, &SDLRendererInfo);
				engine->platform.renderingAPIVersion = (char*)SDLRendererInfo.name;
			}
		}
	}
}

void Lania::loop(Engine* engine, Application* application)
{
	Timer* time = &engine->timer;
	time->FPS.setStart();

	///////// Temporary Testing (Before Procedures): Entity Component System Loading Algorithms

	Scene2D scene2D;

	Entity2D camera;
	//Assign data, centred to screen
	camera.transform.position_px.x = engine->appConfig.windowWidth_px / 2;
	camera.transform.position_px.y = engine->appConfig.windowHeight_px / 2;
	//Add to scene
	scene2D.entities.push_back(camera);

	Camera2D camera2D;
	//Assign data, viewing the entire scene
	camera2D.viewport_px.width = engine->appConfig.windowWidth_px;
	camera2D.viewport_px.height = engine->appConfig.windowHeight_px;
	camera2D.current = true;
	//Attach to last entity
	camera2D.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= CAMERA2D;
	//Add to scene
	scene2D.activeCameras.push_back(camera2D);
	//Camera assigned as current
	scene2D.currentCameraIndex = scene2D.activeCameras.size() - 1;

	//Once again

	Entity2D magnemite;
	magnemite.transform.position_px.x = engine->appConfig.windowWidth_px / 2;
	magnemite.transform.position_px.y = engine->appConfig.windowHeight_px / 2;
	scene2D.entities.push_back(magnemite);

	Sprite magnemiteSprite;
	SDL_Surface* magnemiteSurface =
		IMG_Load("../Demos/SpriteTest/SpriteTest/Graphics/Textures/Magnemite_small.png");
	magnemiteSprite.texture = SDL_CreateTextureFromSurface(engine->SDLRenderer, magnemiteSurface);
	magnemiteSprite.pixels.width = magnemiteSurface->w;
	magnemiteSprite.pixels.height = magnemiteSurface->h;
	SDL_FreeSurface(magnemiteSurface);
	magnemiteSprite.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= SPRITE;
	scene2D.activeSprites.push_back(magnemiteSprite);

	Entity2D apple;
	//As an attached entity, these are relative to magnemite
	apple.transform.position_px.x = 0;
	apple.transform.position_px.y = -100;
	//Attach apple to magnemite
	apple.parent = scene2D.entities.size() - 1;
	scene2D.entities.back().children.push_back(scene2D.entities.size());
	//Add to scene.
	scene2D.entities.push_back(apple);

	Sprite appleSprite;
	SDL_Surface* appleSurface =
		IMG_Load("../Demos/SpriteTest/SpriteTest/Graphics/Textures/apple.png");
	appleSprite.texture = SDL_CreateTextureFromSurface(engine->SDLRenderer, appleSurface);
	appleSprite.pixels.width = appleSurface->w;
	appleSprite.pixels.height = appleSurface->h;
	SDL_FreeSurface(appleSurface);
	appleSprite.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= SPRITE;
	scene2D.activeSprites.push_back(appleSprite);

	application->scene.subscenes2D.push_back(scene2D);

	////////////

	do
	{
		time->frame.setStart();
		time->process.setStart();

		time->lag_ms += time->frame.delta_ns / MS_PER_NS;

		OS::listenForEvents(engine);
		Lania::script(engine, application);
		Lania::compute(engine, application);
		Lania::output(engine, application);

		time->process.setEnd();
		
		//0 or less for unlimited FPS use.
		if (engine->appConfig.targetFPS > 0)
		{
			int delay = (1000.0 / engine->appConfig.targetFPS) -
				(engine->timer.process.delta_ns / MS_PER_NS);
			if (delay > 0)
				SDL_Delay(delay);
		}
		time->frame.setEnd();
		engine->frameCount++;

		static int passedFrames;
		passedFrames++;
		time->FPS.setEnd();
#ifdef _DEBUG
		//Display FPS and other data to Window title.
		if (time->FPS.delta_ns / MS_PER_NS >= MS_PER_S)
		{
			engine->FPS = (passedFrames / (time->FPS.delta_ns / S_PER_NS));
			time->FPS.setStart();
			passedFrames = 1;

			String rendererString;
			switch (engine->renderer)
			{
				case SDL_RENDERER: rendererString = "SDL"; break;
				case LANIA_OPENGL_RENDERER:
				case LANIA_VULKAN_RENDERER: rendererString = "Lania"; break;
			}

			String FPSString = std::to_string(engine->FPS);
			String frameUtilizationString = 
				std::to_string((int)(((double)time->process.delta_ns / (double)time->frame.delta_ns) * 100));
			String batteryString = std::to_string(engine->platform.batteryLife_pct);
			SDL_SetWindowTitle(engine->window,
				(engine->appConfig.appName + " - Lania Engine Debug ->" + 
					" Renderer: " + rendererString + 
					", API: " + engine->platform.renderingAPIVersion + 
					", FPS: " + FPSString +
					", Frame Time Utilization: " + frameUtilizationString + "%" + 
					", Battery: " + batteryString + "%").c_str());
		}
#endif
	} while (engine->state != SHUTDOWN);
}

void Lania::script(Engine* engine, Application* application)
{
	Timer* time = &engine->timer;
	time->script.setStart();

	time->script.setEnd();
}

void Lania::compute(Engine* engine, Application* application)
{
	Timer* time = &engine->timer;
	time->compute.setStart();

	while (time->lag_ms >= MS_PER_UPDATE)
	{
		//Development test
		//Rotate magnemite through List reference. Pointers dangle after auto-reallocation.
		application->scene.subscenes2D.at(0).entities.at(1).transform.rotation_rad += 
			(M_PI / 6) * 1 / (engine->appConfig.targetFPS);

		time->simulation_ms += MS_PER_UPDATE;
		time->lag_ms -= MS_PER_UPDATE;
	}
	time->compute.setEnd();
}

void Lania::output(Engine* engine, Application* application)
{
	Timer* time = &engine->timer;
	time->output.setStart();
	if (engine->renderer == LANIA_OPENGL_RENDERER)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SDL_GL_SwapWindow(engine->window);
	}
	else if (engine->renderer == LANIA_VULKAN_RENDERER)
	{
		;
	}
	else if (engine->renderer == SDL_RENDERER)
	{
		RendererSDL::drawSprites(
			engine->SDLRenderer, 
			engine->window, 
			&application->scene.subscenes2D);
	}
	time->output.setEnd();
}

void Lania::shutdown(Engine* engine, Application* application)
{
	List<SDL_GameController*>* gameControllers = &engine->input.gameControllers;
	List<SDL_Haptic*>* haptics = &engine->input.haptics;

	for (int i = 0; i < gameControllers->size(); ++i)
	{
		SDL_GameControllerClose(gameControllers->at(i));
		SDL_HapticClose(haptics->at(i));
	}

	gameControllers->clear();
	haptics->clear();

	if (engine->renderer == LANIA_OPENGL_RENDERER)
		SDL_GL_DeleteContext(engine->glContext);
	else if (engine->renderer == SDL_RENDERER)
		SDL_DestroyRenderer(engine->SDLRenderer);
	SDL_DestroyWindow(engine->window);
	SDL_Quit();
}
