#include "OS.hpp"
#include "Constants.hpp"
#include "Logging.hpp"
#include <Core/Engine.hpp>
#include <Core/Input.hpp>
#include "SDL_events.h"
#include <SDL_image.h>

void Lania::OS::listenForEvents(Lania::Engine* engine)
{
	engine->timer.input.setStart();

	if (SDL_NumJoysticks() != engine->input.gameControllers.size())
		OS::detectGameControllers(engine);
	OS::detectBatteryLife(engine);
	OS::pollInputEvents(engine);
//	OS::refreshWindowIcon(engine);

	engine->timer.input.setEnd();
}

void Lania::OS::detectGameControllers(Engine* engine)
{
	for (int i = 0; i < engine->input.gameControllers.size(); ++i)
	{
		SDL_GameControllerClose(engine->input.gameControllers.at(i));
		SDL_HapticClose(engine->input.haptics.at(i));
	}

	engine->input.gameControllers.clear();
	engine->input.haptics.clear();

	for (int i = 0; i < SDL_NumJoysticks(); ++i)
	{
		if (SDL_IsGameController(i))
		{
			SDL_GameController* newController = SDL_GameControllerOpen(i);
			SDL_Joystick* joystick = SDL_GameControllerGetJoystick(newController);
			engine->input.gameControllers.push_back(newController);
			engine->input.haptics.push_back(SDL_HapticOpenFromJoystick(joystick));
			if (!engine->input.gameControllers.back())
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

void Lania::OS::refreshWindowIcon(Engine* engine)
{
	engine->timer.run.setEnd();
	if (engine->timer.run.delta_ns / S_PER_NS >= 10)
	{
		String iconString = "../Demos/" + engine->appConfig.appName + "/Icon.png";
		SDL_Surface* logo = IMG_Load(iconString.c_str());
		SDL_SetWindowIcon(engine->window, logo);
		SDL_FreeSurface(logo);
	}
}