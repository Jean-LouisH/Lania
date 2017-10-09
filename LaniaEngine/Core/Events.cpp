#include "Events.hpp"
#include "Logging.hpp"
#include <SDL_events.h>

bool handleEvents()
{
	SDL_Event SDLEvents;
	bool isRunning = true;

	while (SDL_PollEvent(&SDLEvents))
	{
		switch (SDLEvents.type)
		{
			/*Close window button*/
		case SDL_QUIT:
			isRunning = false;
			break;

			/*Keyboard inputs*/
		case SDL_KEYDOWN:
			if (SDLEvents.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
			}
			break;
		}
	}

	return isRunning;
}