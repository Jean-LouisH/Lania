#include "LaniaEngine.hpp"
#include <GL\glew.h>
#include <SDL.h>

Lania::EngineData Lania::initialize()
{
	EngineData engine;
	engine.state = RUNNING;

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log(
			"SDL could not initialize because: %s",
			SDL_GetError);
		engine.state = SHUTDOWN;
	}
	else
	{
		engine.targetFPS = 60;
		engine.windowWidthPixels = 800;
		engine.windowHeightPixels = 600;

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		engine.window = SDL_CreateWindow(
			"Lania Engine",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			engine.windowWidthPixels,
			engine.windowHeightPixels,
			SDL_WINDOW_OPENGL);

		if (engine.window == NULL)
		{
			SDL_Log(
				"SDL could not create the window because: %s",
				SDL_GetError());
			engine.state = SHUTDOWN;
		}

		engine.glContext = SDL_GL_CreateContext(engine.window);
		glViewport(0, 0, engine.windowWidthPixels, engine.windowHeightPixels);

		if (glewInit() != GLEW_OK)
		{
			engine.state = SHUTDOWN;
		}

		engine.glVersion = glGetString(GL_VERSION);
	}
	return engine;
}

void Lania::shutdown(EngineData* engine)
{
	SDL_GL_DeleteContext(engine->glContext);
	SDL_DestroyWindow(engine->window);
	SDL_Quit();
}