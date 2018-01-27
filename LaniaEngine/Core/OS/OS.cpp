#include "OS.hpp"
#include "Logging.hpp"
#include "../Engine.hpp"
#include "../Input.hpp"
#include "SDL_events.h"

void OS::listenForEvents(Lania::Engine* engine)
{
	SDL_Event SDLEvents;
	engine->time.input.setStart();
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
				engine->keyBuffer[SDLEvents.key.keysym.sym] = Key::KEY_DOWN;
				engine->keyEvents.push_back({
					Key::KEY_DOWN,
					SDLEvents.key.keysym.sym,
					SDLEvents.key.timestamp });
			}
			break;
		case SDL_KEYUP:
			if (SDLEvents.key.keysym.sym < 128)
			{
				engine->keyBuffer[SDLEvents.key.keysym.sym] = Key::KEY_UP;
				engine->keyEvents.push_back({
					Key::KEY_UP,
					SDLEvents.key.keysym.sym,
					SDLEvents.key.timestamp });
			}
			break;
		}
	}
	engine->time.input.setEnd();
}