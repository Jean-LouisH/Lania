/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Event System
*
* Handles the operating system events for the engine.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <SDL.h>

namespace Lania
{
	typedef struct
	{
		bool isRunning;
		bool keyboardBuffer[128];
	}Messages;

	class EventSystem
	{
	private:
		SDL_Event SDLEvents;
		Messages messages;
	public:
		Messages handleSDLEvents();
	};
}
