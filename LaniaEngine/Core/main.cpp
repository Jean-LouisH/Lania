/**
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Lania Engine, named after the Laniakea Supercluster
* (Hawaiian for "immeasurable heaven"), is a 2D/3D
* real-time simulation and game engine.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* Created: 5th March 2017
*/

#include <SDL.h>
#include <GL/glew.h>

#include "Timing.hpp"
#include "Logging.hpp"
#include "Events.hpp"

#undef main main //reverses SDL's main definition.

namespace Lania
{
	bool initialize(
		SDL_Window** window,
		SDL_GLContext* glContext);
	void shutdown(
		SDL_Window* window,
		SDL_GLContext glContext);
}

int main()
{
	SDL_Window *window = NULL;
	SDL_GLContext context;
	Lania::Timing timing = {0.0};
	bool isRunning = Lania::initialize(&window, &context);

	while(isRunning)
	{
		isRunning = handleEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
		timing.current = SDL_GetTicks();
		timing.simulation += (timing.current - timing.last);
		timing.last = timing.current;
		SDL_Delay(1000 / 60);
	}

	Lania::shutdown(window, context);
	return 0;
}

bool Lania::initialize(
	SDL_Window** window,
	SDL_GLContext* glContext)
{
	int windowWidth = 800;
	int windowHeight = 600;

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log(
			"SDL could not initialize because: %s", 
			SDL_GetError);
		return false;
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		*window = SDL_CreateWindow(
			"Lania Engine",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			windowWidth,
			windowHeight,
			SDL_WINDOW_OPENGL);

		if (*window == NULL)
		{
			SDL_Log(
				"SDL could not create the window because: %s",
				SDL_GetError());
			return false;
		}

		*glContext = SDL_GL_CreateContext(*window);
		glViewport(0, 0, windowWidth, windowHeight);

		if (glewInit() != GLEW_OK)
		{
			return false;
		}

		return true;
	}
}

void Lania::shutdown(
	SDL_Window* window,
	SDL_GLContext glContext)
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
