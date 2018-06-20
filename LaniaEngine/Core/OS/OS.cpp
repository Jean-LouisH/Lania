#include "OS.hpp"
#include "Logging.hpp"
#include <Core/Engine.hpp>
#include <Core/Input.hpp>
#include "SDL_events.h"

void Lania::OS::listenForEvents(Lania::Engine* engine)
{
	SDL_Event SDLEvents;
	engine->timer.input.setStart();

	if (SDL_NumJoysticks() != engine->input.gameControllers.size())
	{
		engine->input.gameControllers.clear();

		for (int i = 0; i < SDL_NumJoysticks(); ++i)
		{
			if (SDL_IsGameController(i))
			{
				engine->input.gameControllers.push_back(SDL_GameControllerOpen(i));
				if (!engine->input.gameControllers.back())
					fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}

	while (SDL_PollEvent(&SDLEvents))
	{
		switch (SDLEvents.type)
		{
			/*Close window button*/
		case SDL_QUIT:
			engine->state = Lania::SHUTDOWN;
			break;

			/*Keyboard inputs*/
		case SDL_KEYDOWN:
			if (SDLEvents.key.keysym.sym == SDLK_ESCAPE)
			{
				engine->state = Lania::SHUTDOWN;
			}
			else
			{
				engine->input.keyEvents.push_back({
					Key::KEY_DOWN,
					SDLEvents.key.keysym.sym,
					SDLEvents.key.timestamp });
			}
			break;
		case SDL_KEYUP:
			engine->input.keyEvents.push_back({
				Key::KEY_UP,
				SDLEvents.key.keysym.sym,
				SDLEvents.key.timestamp });
			break;
		}
	}
	engine->timer.input.setEnd();
}
