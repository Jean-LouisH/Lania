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
#include "Timing.hpp"

#undef main main //reverses SDL's main definition.

int main()
{
	Lania::Timing timing = {0.0};

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log("SDL could not initialize because: %s", SDL_GetError);
		return 1;
	}
	else
	{
		
	}

	do
	{
		SDL_Delay((int)(1000 / 60));
		timing.current = SDL_GetTicks();
		double deltaMilliseconds = (timing.current - timing.last);
		timing.simulation += deltaMilliseconds;
		timing.last = timing.current;
	} while (true);

	SDL_Quit();

	return 0;
}
