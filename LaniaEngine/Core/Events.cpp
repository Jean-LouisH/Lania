#include "Events.hpp"
#include "Logging.hpp"
#include "EngineData.hpp"
#include <SDL_events.h>

unsigned char OSEvents::handle()
{
	SDL_Event SDLEvents;
	unsigned char state = Lania::gameStates::RUNNING;

	while (SDL_PollEvent(&SDLEvents))
	{
		switch (SDLEvents.type)
		{
			/*Close window button*/
		case SDL_QUIT:
			state = Lania::gameStates::SHUTDOWN;
			break;

			/*Keyboard inputs*/
		case SDL_KEYDOWN:
			if (SDLEvents.key.keysym.sym == SDLK_ESCAPE)
			{
				state = Lania::gameStates::SHUTDOWN;
			}
			break;
		}
	}

	return state;
}