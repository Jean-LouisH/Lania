#include "LaniaEngine.hpp"
#include "Configuration.hpp"
#include "EngineData.hpp"
#include "../Input/Keyboard.hpp"
#include "OS/File.hpp"
#include <GL/glew.h>
#include <SDL.h>

Lania::EngineData Lania::initialize()
{
	//Development Test 
	std::string initFilePath = "../Demos/Basic/Init.cfg";

	EngineData engine = Config::parseInit(File::read(initFilePath));
	engine.state = RUNNING;
	engine.APIVersion = NULL;
	engine.glContext = NULL;
	engine.platform = (char*)SDL_GetPlatform();

	for (int i = 0; i < KEY_BUFFER_SIZE; i++)
	{
		engine.keyBuffer[i] = NEUTRAL;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log(
			"SDL could not initialize because: %s",
			SDL_GetError);
		engine.state = SHUTDOWN;
	}
	else
	{
		if (engine.windowFlags & SDL_WINDOW_OPENGL)
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
		else if (engine.windowFlags & SDL_WINDOW_VULKAN)
		{
			;
		}

		engine.window = SDL_CreateWindow(
			engine.windowTitle.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			engine.windowWidthPixels,
			engine.windowHeightPixels,
			engine.windowFlags);

		if (engine.window == NULL)
		{
			SDL_Log(
				"SDL could not create the window because: %s",
				SDL_GetError());
			engine.state = SHUTDOWN;
		}

		if (engine.windowFlags & SDL_WINDOW_OPENGL)
		{
			engine.glContext = SDL_GL_CreateContext(engine.window);
			glViewport(0, 0, engine.windowWidthPixels, engine.windowHeightPixels);

			if (glewInit() != GLEW_OK)
			{
				engine.state = SHUTDOWN;
			}
			engine.APIVersion = (char*)glGetString(GL_VERSION);
		}
		else if (engine.windowFlags & SDL_WINDOW_VULKAN)
		{
			;
		}
		engine.targetFPS = 60;
	}
	return engine;
}

void Lania::shutdown(EngineData* engine)
{
	SDL_GL_DeleteContext(engine->glContext);
	SDL_DestroyWindow(engine->window);
	SDL_Quit();
}