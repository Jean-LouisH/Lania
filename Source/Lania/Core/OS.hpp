/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* OS
*
* Receives inputs and events from the keyboard, mouse and OS messages.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "Core.hpp"

namespace Lania
{
	namespace OS
	{
		void detectGameControllers(Input* input);
		void detectBatteryLife(Core* core);
		void pollInputEvents(Core* core);
		void setToWindowed(SDL_Window* window, uint16_t width_px, uint16_t height_px, uint8_t* state);
		void setToFullscreen(SDL_Window* window, SDL_DisplayMode* mode, uint8_t* state);
		void toggleWindowedFullscreen(SDL_Window* window, uint8_t* state);
	}
}
