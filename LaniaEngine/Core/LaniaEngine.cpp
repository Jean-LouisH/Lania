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
	String initFilePath = "../Demos/PhysicsTest/Init.cfg";

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
		SDL_GetDesktopDisplayMode(0, &engine->platform.SDLDisplayMode);
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
		IMG_Load("../Demos/PhysicsTest/PhysicsTest/Graphics/Textures/background.png");
	bgSprite.texture = SDL_CreateTextureFromSurface(engine->SDLRenderer, bgSurface);
	bgSprite.pixels.width = bgSurface->w;
	bgSprite.pixels.height = bgSurface->h;
	SDL_FreeSurface(bgSurface);
	bgSprite.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= SPRITE;
	scene2D.activeSprites.push_back(bgSprite);

	scene2D.entities.back().transform.position_px.x = bgSprite.pixels.width / 2.0;
	scene2D.entities.back().transform.position_px.y = bgSprite.pixels.height / 2.0;

	//Camera position
	scene2D.entities.at(0).transform.position_px.x = bgSprite.pixels.width / 2.0;
	scene2D.entities.at(0).transform.position_px.y = bgSprite.pixels.height / 2.0;
	scene2D.activeCameras.at(scene2D.currentCameraIndex).viewport_px.width = bgSprite.pixels.width;
	scene2D.activeCameras.at(scene2D.currentCameraIndex).viewport_px.height = bgSprite.pixels.width / 1.777;

	///////////

	Entity2D floorCollider;
	floorCollider.transform.position_px.x = 1326 / 2;
	floorCollider.transform.position_px.y = 150;
	floorCollider.transform.scale.x = 15.0;
	scene2D.entities.push_back(floorCollider);

	Sprite2D boxSprite;
	SDL_Surface* boxSurface =
		IMG_Load("../Demos/PhysicsTest/PhysicsTest/Graphics/Textures/box.png");
	boxSprite.texture = SDL_CreateTextureFromSurface(engine->SDLRenderer, boxSurface);
	boxSprite.pixels.width = boxSurface->w;
	boxSprite.pixels.height = boxSurface->h;
	SDL_FreeSurface(boxSurface);
	boxSprite.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= SPRITE;
	scene2D.activeSprites.push_back(boxSprite);

	BoxCollider2D floorBoxCollider;
	floorBoxCollider.aabb.max_px.x = 1400;
	floorBoxCollider.aabb.max_px.y = boxSprite.pixels.height / 2.0;
	floorBoxCollider.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= BOXCOLLIDER2D;
	scene2D.activeBoxColliders.push_back(floorBoxCollider);

	double testScale = 2.5;
	//testScale = 1.0;

	Entity2D beldum;
	beldum.transform.position_px.x = 260;
	beldum.transform.position_px.y = 500;
	beldum.transform.scale.x = testScale;
	beldum.transform.scale.y = testScale;
	scene2D.entities.push_back(beldum);

	RigidBody2D rigid;
	rigid.gravity_scale = 20.0;
	rigid.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= RIGIDBODY2D;
	scene2D.activeRigidBodies.push_back(rigid);

	Sprite2D beldumSprite;
	SDL_Surface* beldumSurface =
		IMG_Load("../Demos/PhysicsTest/PhysicsTest/Graphics/Textures/beldum.png");
	beldumSprite.texture = SDL_CreateTextureFromSurface(engine->SDLRenderer, beldumSurface);
	beldumSprite.pixels.width = beldumSurface->w;
	beldumSprite.pixels.height = beldumSurface->h;
	SDL_FreeSurface(beldumSurface);
	beldumSprite.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= SPRITE;
	scene2D.activeSprites.push_back(beldumSprite);

	BoxCollider2D beldumBoxCollider;
	beldumBoxCollider.aabb.max_px.x = beldumSprite.pixels.width * beldum.transform.scale.x;
	beldumBoxCollider.aabb.max_px.y = beldumSprite.pixels.height * beldum.transform.scale.y;
	beldumBoxCollider.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= BOXCOLLIDER2D;
	scene2D.activeBoxColliders.push_back(beldumBoxCollider);

	//////////

	Entity2D arcanine;
	arcanine.transform.position_px.x = 1326 - 260;
	arcanine.transform.position_px.y = 500;
	arcanine.transform.scale.x = testScale;
	arcanine.transform.scale.y = testScale;
	scene2D.entities.push_back(arcanine);

	rigid.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= RIGIDBODY2D;
	scene2D.activeRigidBodies.push_back(rigid);

	Sprite2D arcanineSprite;
	SDL_Surface* arcanineSurface =
		IMG_Load("../Demos/PhysicsTest/PhysicsTest/Graphics/Textures/arcanine.png");
	arcanineSprite.texture = SDL_CreateTextureFromSurface(engine->SDLRenderer, arcanineSurface);
	arcanineSprite.pixels.width = arcanineSurface->w;
	arcanineSprite.pixels.height = arcanineSurface->h;
	SDL_FreeSurface(arcanineSurface);
	arcanineSprite.entityID = scene2D.entities.size() - 1;
	arcanineSprite.flip = SDL_FLIP_HORIZONTAL;
	scene2D.entities.back().attachedComponentsFlag |= SPRITE;
	scene2D.activeSprites.push_back(arcanineSprite);

	BoxCollider2D arcanineBoxCollider;
	arcanineBoxCollider.aabb.max_px.x = arcanineSprite.pixels.width * arcanine.transform.scale.x;
	arcanineBoxCollider.aabb.max_px.y = arcanineSprite.pixels.height * arcanine.transform.scale.y;
	arcanineBoxCollider.entityID = scene2D.entities.size() - 1;
	scene2D.entities.back().attachedComponentsFlag |= BOXCOLLIDER2D;
	scene2D.activeBoxColliders.push_back(arcanineBoxCollider);

	////////////

	application->scene.subscenes2D.push_back(scene2D);

	////////////

	do
	{
		time->frame.setStart();
		time->process.setStart();

		time->lag_ms += time->frame.delta_ns / MS_PER_NS;

		Lania::input(engine);
		Lania::logic(engine, application);
		Lania::compute(engine, application);
		Lania::output(engine);

		time->process.setEnd();

		int delay = 0;
		
		if (engine->appConfig.targetFPS < UPDATES_PER_S)
		{
			delay = (MS_PER_S / engine->appConfig.targetFPS) -
				(engine->timer.process.delta_ns / MS_PER_NS);
		}
		else
		{
			delay = (MS_PER_S / UPDATES_PER_S) -
				(engine->timer.process.delta_ns / MS_PER_NS);
		}

		if (delay > 0)
			SDL_Delay(delay);

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

void Lania::input(Lania::Engine* engine)
{
	engine->timer.OS.setStart();

	if (SDL_NumJoysticks() != engine->input.gameControllers.size())
		OS::detectGameControllers(&engine->input);
	OS::detectBatteryLife(engine);
	OS::pollInputEvents(engine);

	engine->timer.OS.setEnd();
}

void Lania::logic(Engine* engine, Application* application)
{
	Timer* time = &engine->timer;
	time->script.setStart();

	List<Scene2D>* scene2Ds = &application->scene.subscenes2D;
	if (scene2Ds->size() > 0)
	{
		Physics2D::detectCollisions(scene2Ds);
	}

	if (engine->renderer == SDL_RENDERER)
	{
		RendererSDL::buildRenderablesFromSprites(
			&engine->output.SDLRenderables,
			&application->scene.subscenes2D,
			engine->window
		);
	}

	time->script.setEnd();
}

void Lania::compute(Engine* engine, Application* application)
{
	Timer* time = &engine->timer;
	time->compute.setStart();

	while (time->lag_ms >= MS_PER_UPDATE)
	{
		List<Scene2D>* scene2Ds = &application->scene.subscenes2D;
		if (scene2Ds->size() > 0)
		{
			Physics2D::gravitate(scene2Ds);
			Physics2D::displace(scene2Ds);
			Physics2D::lock(scene2Ds);
		}
		time->simulation_ms += MS_PER_UPDATE;
		time->lag_ms -= MS_PER_UPDATE;
	}
	time->compute.setEnd();
}

void Lania::output(Engine* engine)
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
		SDL_SetRenderDrawColor(engine->SDLRenderer, 0, 0, 0, 255);
		SDL_RenderClear(engine->SDLRenderer);

		int renderableCount = engine->output.SDLRenderables.size();
		SDLRenderable* renderables = engine->output.SDLRenderables.data();
		for (int i = 0; i < renderableCount; i++)
			SDL_RenderCopyEx(
				engine->SDLRenderer,
				renderables[i].texture,
				&renderables[i].textureRect,
				&renderables[i].renderingRect,
				renderables[i].rotation,
				NULL,
				renderables[i].flip);

		SDL_RenderPresent(engine->SDLRenderer);
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
