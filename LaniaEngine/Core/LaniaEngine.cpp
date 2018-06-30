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
			String iconString = "../Demos/" + appConfig->appName + "/Icon.png";
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
				String* renderingAPIString = new String;
				*renderingAPIString += "OpenGL ";
				*renderingAPIString += (char*)glGetString(GL_VERSION);
				engine->platform.renderingAPIVersion = (char*)renderingAPIString->c_str();
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

	Scene2D scene2D;
	Entity2D cameraEntity;
	Camera2D camera;
	cameraEntity.transform.position_px.x = engine->appConfig.windowWidth_px / 2;
	cameraEntity.transform.position_px.y = engine->appConfig.windowHeight_px / 2;
	camera.viewport_px.width = engine->appConfig.windowWidth_px;
	camera.viewport_px.height = engine->appConfig.windowHeight_px;
	camera.current = true;
	Entity2D magnemite;
	magnemite.transform.position_px.x = engine->appConfig.windowWidth_px / 2;
	magnemite.transform.position_px.y = engine->appConfig.windowHeight_px / 2;
	cameraEntity.id = 1;
	magnemite.id = 2;
	Sprite sprite;
	SDL_Surface* surface =
		IMG_Load("../Demos/SpriteTest/SpriteTest/Graphics/Textures/Magnemite_small.png");
	sprite.texture = SDL_CreateTextureFromSurface(engine->SDLRenderer, surface);
	sprite.pixels.width = surface->w;
	sprite.pixels.height = surface->h;
	SDL_FreeSurface(surface);
	cameraEntity.components.insert(Pair<uint8_t, uint64_t>(CAMERA2D, (uint64_t)&camera));
	magnemite.components.insert(Pair<uint8_t, uint64_t>(SPRITE, (uint64_t)&sprite));
	camera.container = &cameraEntity;
	sprite.container = &magnemite;
	scene2D.cameras.push_back(camera);
	scene2D.sprites.push_back(sprite);
	scene2D.entities.push_back(magnemite);
	application->scene.subscenes2D.push_back(scene2D);

	do
	{
		magnemite.transform.rotation_rad += (M_PI / 6) * 1 / (engine->appConfig.targetFPS);
		time->frame.setStart();
		time->cycle.setStart();

		time->lag += time->frame.delta_ns / MS_PER_NS;

		OS::listenForEvents(engine);
		Lania::script(engine, application);
		Lania::compute(engine, application);
		Lania::output(engine, application);

		time->cycle.setEnd();
		
		//0 or less for unlimited FPS use.
		if (engine->appConfig.targetFPS > 0)
		{
			int delay = (1000.0 / engine->appConfig.targetFPS) -
				(engine->timer.cycle.delta_ns / MS_PER_NS);
			if (delay > 0)
				SDL_Delay(delay);
		}
		time->frame.setEnd();
		engine->frameCount++;

		static int passedFrames;
		passedFrames++;
		time->FPS.setEnd();
#ifdef _DEBUG
		if (time->FPS.delta_ns / MS_PER_NS >= MS_PER_S)
		{
			engine->FPS = (passedFrames / (time->FPS.delta_ns / S_PER_NS));
			time->FPS.setStart();
			passedFrames = 1;

			String rendererString;
			switch (engine->renderer)
			{
				case SDL_RENDERER: rendererString = "SDL"; break;
				case LANIA_OPENGL_RENDERER: rendererString = "Lania"; break;
				case LANIA_VULKAN_RENDERER: rendererString = "Lania"; break;
			}

			String FPSString = std::to_string(engine->FPS);
			String frameUtilizationString = 
				std::to_string((int)(((double)time->cycle.delta_ns / (double)time->frame.delta_ns) * 100));
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
	while (time->lag >= MS_PER_UPDATE)
	{
		time->simulation += MS_PER_UPDATE;
		time->lag -= MS_PER_UPDATE;
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
