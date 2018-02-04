#include "LaniaEngine.hpp"
#include "Configuration.hpp"
#include "Engine.hpp"
#include "Input.hpp"
#include "OS/File.hpp"
#include "OS/OS.hpp"
#include "GL/glew.h"
#include "../Constants.hpp"
#include "SDL.h"
#include <sstream>

void Lania::initialize(Engine* engine)
{
	//Development Test 
	std::string initFilePath = "../Demos/IncrementTest/Init.cfg";

	AppConfig* appConfig = &engine->appConfig;
	unsigned char* state = &engine->state;

	*appConfig = Config::parseInit(File::read(initFilePath));
	engine->platform = (char*)SDL_GetPlatform();
	*state = RUNNING_APPLICATION;

	for (int i = 0; i < KEY_BUFFER_SIZE; i++)
	{
		engine->input.keyBuffer[i] = Key::KEY_NEUTRAL;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log(
			"SDL could not initialize because: %s",
			SDL_GetError);
		*state = SHUTDOWN;
	}
	else
	{
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
			appConfig->windowWidthPixels,
			appConfig->windowHeightPixels,
			appConfig->windowFlags);

		if (engine->window == NULL)
		{
			SDL_Log(
				"SDL could not create the window because: %s",
				SDL_GetError());
			*state = SHUTDOWN;
		}

		if (appConfig->windowFlags & SDL_WINDOW_OPENGL)
		{
			engine->glContext = SDL_GL_CreateContext(engine->window);
			glViewport(0, 0, appConfig->windowWidthPixels, appConfig->windowHeightPixels);

			if (glewInit() != GLEW_OK)
			{
				*state = SHUTDOWN;
			}
			engine->renderingAPI = (char*)glGetString(GL_VERSION);
		}
		else if (appConfig->windowFlags & SDL_WINDOW_VULKAN)
		{
			;
		}
		appConfig->targetFPS = 60;
	}
}

void Lania::loop(Engine* engine, Application* application)
{
	Timer* time = &engine->timer;
	time->FPS.setStart();

	//Development Test
	application->loadScene(
		"../Demos/IncrementTest/" +
		engine->appConfig.appName +
		"/Scenes/" +
		engine->appConfig.mainScene);

	while (engine->state != SHUTDOWN)
	{
		time->frame.setStart();
		time->cycle.setStart();

		time->lag += time->frame.delta / MS_PER_NS;

		OS::listenForEvents(engine);
		Lania::script(engine, application);
		Lania::compute(engine, application);
		Lania::output(engine);

		time->cycle.setEnd();
		if (engine->appConfig.targetFPS > 0)
		{
			int delay = (1000.0 / engine->appConfig.targetFPS) -
				(engine->timer.cycle.delta / MS_PER_NS);
			if (delay > 0)
				SDL_Delay(delay);
		}
		time->frame.setEnd();
		engine->frameCount++;

		static int passedFrames;
		passedFrames++;
		time->FPS.setEnd();
		if (time->FPS.delta / MS_PER_NS >= 1000)
		{
			engine->FPS = (passedFrames / (time->FPS.delta / S_PER_NS));
			time->FPS.setStart();
			passedFrames = 1;
			std::string FPSString = std::to_string(engine->FPS);
			SDL_SetWindowTitle(engine->window,
				(engine->appConfig.appName + " - FPS:" + FPSString).c_str());
		}
	}
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

void Lania::output(Engine* engine)
{
	Timer* time = &engine->timer;
	time->output.setStart();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(engine->window);
	time->output.setEnd();
}

void Lania::shutdown(Engine* engine, Application* application)
{
	SDL_GL_DeleteContext(engine->glContext);
	SDL_DestroyWindow(engine->window);
	SDL_Quit();
}
