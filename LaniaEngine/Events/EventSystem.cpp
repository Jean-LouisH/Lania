#include "EventSystem.hpp"

Lania::Messages Lania::EventSystem::handleSDLEvents()
{
	messages.isRunning = true;

	while (SDL_PollEvent(&SDLEvents))
	{
		switch (SDLEvents.type)
		{
			/*Close window button*/
		case SDL_QUIT:
			messages.isRunning = false;
			break;

			/*Keyboard inputs*/
		case SDL_KEYDOWN:
			if (SDLEvents.key.keysym.sym == SDLK_ESCAPE)
			{
				messages.isRunning = false;
			}
			else if (SDLEvents.key.keysym.sym < 128) //ASCII values are below 128.
			{
				messages.keyboardBuffer[SDLEvents.key.keysym.sym] = true;
			}
			break;

		case SDL_KEYUP:
			if (SDLEvents.key.keysym.sym < 128)
			{
				messages.keyboardBuffer[SDLEvents.key.keysym.sym] = false;
			}
			break;
		}
	}

	return messages;
}
