#include "OS.hpp"
#include "Logging.hpp"
#include "../Engine.hpp"
#include "../Input.hpp"
#include "SDL_events.h"

void Lania::OS::listenForEvents(Lania::Engine* engine)
{
	SDL_Event SDLEvents;
	engine->timer.input.setStart();
	engine->state = Lania::engineStates::RUNNING_APPLICATION;

	while (SDL_PollEvent(&SDLEvents))
	{
		switch (SDLEvents.type)
		{
			/*Close window button*/
		case SDL_QUIT:
			engine->state = Lania::engineStates::SHUTDOWN;
			break;

			/*Keyboard inputs*/
		case SDL_KEYDOWN:
			if (SDLEvents.key.keysym.sym == SDLK_ESCAPE)
			{
				engine->state = Lania::engineStates::SHUTDOWN;
			}
			else if (SDLEvents.key.keysym.sym < 128) //ASCII values are below 128.
			{
				engine->input.keyEvents.push_back({
					Key::KEY_DOWN,
					SDLEvents.key.keysym.sym,
					SDLEvents.key.timestamp });
			}
			break;
		case SDL_KEYUP:
			if (SDLEvents.key.keysym.sym < 128)
			{
				engine->input.keyEvents.push_back({
					Key::KEY_UP,
					SDLEvents.key.keysym.sym,
					SDLEvents.key.timestamp });
			}
			break;
		}
	}
	engine->timer.input.setEnd();
}
