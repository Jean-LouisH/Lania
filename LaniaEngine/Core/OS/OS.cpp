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
	MouseState* mouse = &engine->input.mouse;

	engine->input.releasedKeys.clear();

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
				KeyEvent press;
				press.mod = SDLEvents.key.keysym.mod;
				press.timestamp_ms = SDLEvents.key.timestamp;

				engine->input.pressedKeys.emplace(SDLEvents.key.keysym.sym, press);
			}
			break;
		case SDL_KEYUP:
			KeyEvent release;
			release.mod = SDLEvents.key.keysym.mod;
			release.timestamp_ms = SDLEvents.key.timestamp;

			engine->input.releasedKeys.emplace(SDLEvents.key.keysym.sym, release);
			engine->input.pressedKeys.erase(SDLEvents.key.keysym.sym);
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

void Lania::OS::setToWindowed(SDL_Window* window, AppConfig* config)
{
	SDL_SetWindowFullscreen(window, 0);
	SDL_SetWindowSize(window, config->windowWidth_px, config->windowHeight_px);
}

void Lania::OS::setToFullscreen(SDL_Window* window, SDL_DisplayMode* mode)
{
	SDL_SetWindowDisplayMode(window, mode);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void Lania::OS::toggleWindowedFullscreen(SDL_Window* window)
{
	static bool isFullscreen = false;

	if (!isFullscreen)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
	{
		SDL_SetWindowFullscreen(window, 0);
		SDL_SetWindowPosition(
			window,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED);
	}

	SDL_ShowCursor(isFullscreen);
	isFullscreen = !isFullscreen;
}