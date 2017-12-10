#include "OS.hpp"
#include "Logging.hpp"
#include "../EngineData.hpp"
#include "../../Input/Keyboard.hpp"
#include "SDL_events.h"

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
			else if (SDLEvents.key.keysym.sym < 128) //ASCII values are below 128.
			{
				engine->keyBuffer[SDLEvents.key.keysym.sym] = Input::DOWN;
				engine->keyEvents.push_back({
					Input::DOWN,
					SDLEvents.key.keysym.sym,
					SDLEvents.key.timestamp });
			}
			break;
		case SDL_KEYUP:
			if (SDLEvents.key.keysym.sym < 128)
			{
				engine->keyBuffer[SDLEvents.key.keysym.sym] = Input::UP;
				engine->keyEvents.push_back({
					Input::UP,
					SDLEvents.key.keysym.sym,
					SDLEvents.key.timestamp });
			}
			break;
		}
	}
}