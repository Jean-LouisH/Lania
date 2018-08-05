#include "OS.hpp"
#include "Constants.hpp"
#include "Logging.hpp"
#include <Core/Engine.hpp>
#include <Core/Input.hpp>
#include "SDL_events.h"
#include <SDL_image.h>

void Lania::OS::detectGameControllers(Input* input)
{
	for (int i = 0; i < input->gameControllers.size(); ++i)
	{
		SDL_GameControllerClose(input->gameControllers.at(i));
		SDL_HapticClose(input->haptics.at(i));
	}

	input->gameControllers.clear();
	input->haptics.clear();

	for (int i = 0; i < SDL_NumJoysticks(); ++i)
	{
		if (SDL_IsGameController(i))
		{
			SDL_GameController* newController = SDL_GameControllerOpen(i);
			SDL_Joystick* joystick = SDL_GameControllerGetJoystick(newController);
			input->gameControllers.push_back(newController);
			input->haptics.push_back(SDL_HapticOpenFromJoystick(joystick));
			if (!input->gameControllers.back())
				fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
		}
	}
}

void Lania::OS::detectBatteryLife(Engine* engine)
{
	engine->timer.run.setEnd();
	if (engine->timer.run.delta_ns / S_PER_NS >= 10)
		SDL_GetPowerInfo(NULL, &engine->platform.batteryLife_pct);
}

void Lania::OS::pollInputEvents(Engine* engine)
{
	SDL_Event SDLEvents;

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
}

void Lania::OS::toggleFullscreen(SDL_Window* window)
{
	static bool isFullscreen = false;
	static int previousWindowWidth = 0;
	static int previousWindowHeight = 0;

	if (!isFullscreen)
	{
		SDL_GetWindowSize(window, &previousWindowWidth, &previousWindowHeight);
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
	{
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowSize(window, previousWindowWidth, previousWindowHeight);
		SDL_SetWindowPosition(
			window,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED);
	}

	SDL_ShowCursor(isFullscreen);
	isFullscreen = !isFullscreen;
}