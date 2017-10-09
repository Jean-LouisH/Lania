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
#include "Logging.hpp"
#include "Events.hpp"

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

	while(handleEvents())
	{
		timing.current = SDL_GetTicks();
		timing.simulation += (timing.current - timing.last);
		timing.last = timing.current;
		SDL_Delay(1000 / 60);
	}

	SDL_Quit();

	return 0;
}
