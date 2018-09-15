/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* OS
*
* Receives inputs and events from the keyboard, mouse and OS messages.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <Core/Core.hpp>

namespace Lania
{
	namespace OS
	{
		void detectGameControllers(Input* input);
		void detectBatteryLife(Core* core);
		void pollInputEvents(Core* core);
		void setToWindowed(SDL_Window* window, AppConfig* config, uint8_t* state);
		void setToFullscreen(SDL_Window* window, SDL_DisplayMode* mode, uint8_t* state);
		void toggleWindowedFullscreen(SDL_Window* window, uint8_t* state);
	}
}
