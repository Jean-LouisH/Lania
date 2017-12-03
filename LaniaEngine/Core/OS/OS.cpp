#include "OS.hpp"
#include "Logging.hpp"
#include "../EngineData.hpp"
#include <SDL_events.h>

void OS::handleEvents(Lania::EngineData* engine)
{
	SDL_Event SDLEvents;
	engine->state = Lania::gameStates::RUNNING;

	while (SDL_PollEvent(&SDLEvents))
	{
		switch (SDLEvents.type)
		{
			/*Close window button*/
		case SDL_QUIT:
			engine->state = Lania::gameStates::SHUTDOWN;
			break;

			/*Keyboard inputs*/
		case SDL_KEYDOWN:
			if (SDLEvents.key.keysym.sym == SDLK_ESCAPE)
			{
				engine->state = Lania::gameStates::SHUTDOWN;
			}
			break;
		}
	}
}