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
#include <Physics/Physics2D.hpp>
#include <sstream>

void Lania::initialize(Engine* engine)
{
	//Development Test 
	String initFilePath = "../Demos/IsleFightPrototypeReplica/Init.cfg";

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
		IMG_Init(IMG_INIT_JPG);

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

	///////////////////////////////////////////////////////////////////////
	Entity2D camera;
	scene2D.entities.push_back(camera);

	Camera2D camera2D;
	camera2D.viewport_px.width = engine->appConfig.windowWidth_px;
	camera2D.viewport_px.height = engine->appConfig.windowHeight_px;
	camera2D.current = true;
	camera2D.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= CAMERA2D;
	scene2D.activeCameras.push_back(camera2D);
	scene2D.currentCameraIndex = scene2D.activeCameras.size() - 1;
	////////////////////////////////////////////////////////////////////////

	Entity2D background;
	scene2D.entities.push_back(background);

	Sprite2D bgSprite;
	SDL_Surface* bgSurface =
		IMG_Load("../Demos/IsleFightPrototypeReplica/IsleFightPrototypeReplica/Graphics/Textures/beach.jpg");
	bgSprite.texture = SDL_CreateTextureFromSurface(engine->SDLRenderer, bgSurface);
	bgSprite.pixels.width = bgSurface->w;
	bgSprite.pixels.height = bgSurface->h;
	SDL_FreeSurface(bgSurface);
	bgSprite.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= SPRITE;
	scene2D.activeSprites.push_back(bgSprite);

	scene2D.entities.back().transform.position_px.x = bgSprite.pixels.width / 2.0;
	scene2D.entities.back().transform.position_px.y = bgSprite.pixels.height / 2.0;

	scene2D.entities.at(0).transform.position_px.x = bgSprite.pixels.width / 2.0;
	scene2D.entities.at(0).transform.position_px.y = bgSprite.pixels.height / 2.0;
	scene2D.activeCameras.at(scene2D.currentCameraIndex).viewport_px.width = bgSprite.pixels.width;
	scene2D.activeCameras.at(scene2D.currentCameraIndex).viewport_px.height = bgSprite.pixels.width / 1.777;

	double testScale = 0.35;
	//testScale = 1.0;

	Entity2D pikachu1;
	pikachu1.transform.position_px.x = 260;
	pikachu1.transform.position_px.y = 500;
	pikachu1.transform.scale.x = testScale;
	pikachu1.transform.scale.y = testScale;
	scene2D.entities.push_back(pikachu1);

	RigidBody2D pkRigid;
	pkRigid.gravity_scale = 20.0;
	pkRigid.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= RIGIDBODY2D;
	scene2D.activeRigidBodies.push_back(pkRigid);

	Sprite2D pkSprite;
	SDL_Surface* pkSurface =
		IMG_Load("../Demos/IsleFightPrototypeReplica/IsleFightPrototypeReplica/Graphics/Textures/pikachu.png");
	pkSprite.texture = SDL_CreateTextureFromSurface(engine->SDLRenderer, pkSurface);
	pkSprite.pixels.width = pkSurface->w;
	pkSprite.pixels.height = pkSurface->h;
	SDL_FreeSurface(pkSurface);
	pkSprite.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= SPRITE;
	scene2D.activeSprites.push_back(pkSprite);

	Entity2D pikachu2;
	pikachu2.transform.position_px.x = 1326 - 260;
	pikachu2.transform.position_px.y = 500;
	pikachu2.transform.scale.x = testScale;
	pikachu2.transform.scale.y = testScale;
	scene2D.entities.push_back(pikachu2);

	pkRigid.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= RIGIDBODY2D;
	scene2D.activeRigidBodies.push_back(pkRigid);

	pkSprite.entityID = scene2D.entities.size() - 1;
	pkSprite.flip = SDL_FLIP_HORIZONTAL;
	scene2D.entities.back().attachedComponentsFlag |= SPRITE;
	scene2D.activeSprites.push_back(pkSprite);

	Entity2D floorCollider;

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
		Physics2D::gravitate(&application->scene.subscenes2D);
		Physics2D::displace(&application->scene.subscenes2D);
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
