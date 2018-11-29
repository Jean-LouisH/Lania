#include "OS.hpp"
#include <Utilities/Definitions/Constants.hpp>
#include "Logging.hpp"
#include <Core/Core.hpp>
#include "Input.hpp"
#include "SDL_events.h"
#include <SDL_image.h>
#include <stdint.h>

void Lania::OS::detectGameControllers(Input* input)
{
	for (int i = 0; i < input->gameControllers.size(); ++i)
	{
		SDL_GameControllerClose(input->gameControllers.at(i));
		SDL_HapticClose(input->haptics.at(i));
		Log::toConsole("Game Controller " + std::to_string(i) + " Disconnected.");
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
			Log::toConsole("Game Controller " + std::to_string(i) + " Connected.");
		}
	}
}

void Lania::OS::detectBatteryLife(Core* core)
{
	core->timer.run.setEnd();
	if (core->timer.run.delta_ns / NS_IN_S >= 10)
		SDL_GetPowerInfo(NULL, &core->platform.batteryLife_pct);
}

void Lania::OS::pollInputEvents(Core* core)
{
	SDL_Event SDLEvents;
	MouseState* mouse = &core->input.mouse;

	core->input.releasedKeys.clear();

	while (SDL_PollEvent(&SDLEvents))
	{
		switch (SDLEvents.type)
		{
			/*Close window button*/
		case SDL_QUIT:
			core->state = Lania::SHUTDOWN;
			break;

			/*Keyboard inputs*/
		case SDL_KEYDOWN:
			if (SDLEvents.key.keysym.sym == SDLK_ESCAPE)
			{
				core->state = Lania::SHUTDOWN;
			}
			else
			{
				KeyEvent press;
				press.mod = SDLEvents.key.keysym.mod;
				press.timestamp_ms = SDLEvents.key.timestamp;

				core->input.pressedKeys.emplace(SDLEvents.key.keysym.sym, press);
			}
			break;
		case SDL_KEYUP:
			KeyEvent release;
			release.mod = SDLEvents.key.keysym.mod;
			release.timestamp_ms = SDLEvents.key.timestamp;

			core->input.releasedKeys.emplace(SDLEvents.key.keysym.sym, release);
			core->input.pressedKeys.erase(SDLEvents.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse->type = SDL_MOUSEBUTTONDOWN;
			mouse->timestamp_ms = SDLEvents.button.timestamp;
			mouse->windowID = SDLEvents.button.windowID;
			mouse->button = SDLEvents.button.button;
			mouse->buttonState = SDLEvents.button.state;
			mouse->clicks = SDLEvents.button.clicks;
			mouse->x = SDLEvents.button.x;
			mouse->y = SDLEvents.button.y;
			break;
		case SDL_MOUSEBUTTONUP:
			mouse->type = SDL_MOUSEBUTTONUP;
			mouse->timestamp_ms = SDLEvents.button.timestamp;
			mouse->windowID = SDLEvents.button.windowID;
			mouse->button = SDLEvents.button.button;
			mouse->buttonState = SDLEvents.button.state;
			mouse->clicks = SDLEvents.button.clicks;
			mouse->x = SDLEvents.button.x;
			mouse->y = SDLEvents.button.y;
			break;
		case SDL_MOUSEMOTION:
			mouse->type = SDL_MOUSEMOTION;
			mouse->timestamp_ms = SDLEvents.motion.timestamp;
			mouse->windowID = SDLEvents.motion.windowID;
			mouse->motionState = SDLEvents.motion.state;
			mouse->x = SDLEvents.motion.x;
			mouse->y = SDLEvents.motion.y;
			mouse->xrel = SDLEvents.motion.xrel;
			mouse->yrel = SDLEvents.motion.yrel;
			break;
		case SDL_MOUSEWHEEL:
			mouse->type = SDL_MOUSEWHEEL;
			mouse->timestamp_ms = SDLEvents.wheel.timestamp;
			mouse->windowID = SDLEvents.wheel.windowID;
			mouse->xScroll = SDLEvents.wheel.x;
			mouse->yScroll = SDLEvents.wheel.y;
			mouse->direction = SDLEvents.wheel.direction;
			break;
		}
	}
}

void Lania::OS::setToWindowed(SDL_Window* window, uint16_t width, uint16_t height, uint8_t* state)
{
	SDL_SetWindowFullscreen(window, 0);
	SDL_SetWindowSize(window, width, height);
	*state = RUNNING_APPLICATION_WINDOWED;

}

void Lania::OS::setToFullscreen(SDL_Window* window, SDL_DisplayMode* mode, uint8_t* state)
{
	SDL_SetWindowDisplayMode(window, mode);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	*state = RUNNING_APPLICATION_FULLSCREEN;
}

void Lania::OS::toggleWindowedFullscreen(SDL_Window* window, uint8_t* state)
{
	static bool isFullscreen = false;

	if (!isFullscreen)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		*state = RUNNING_APPLICATION_FULLSCREEN_DESKTOP;
	}
	else
	{
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowPosition(
			window,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED);
		*state = RUNNING_APPLICATION_WINDOWED;
	}

	SDL_ShowCursor(isFullscreen);
	isFullscreen = !isFullscreen;
}