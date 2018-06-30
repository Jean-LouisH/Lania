/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Keyboard
*
* Defines the procedures for detecting key presses.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include "SDL_stdinc.h"
#include "SDL_keycode.h"

namespace Lania
{
	namespace Key
	{
		enum keyStates
		{
			KEY_NEUTRAL,
			KEY_DOWN,
			KEY_HELD,
			KEY_UP,
		};

		typedef struct
		{
			Uint8 state;
			SDL_Keycode value;
			Uint32 timestamp_ms;
		}KeyEvent;

		//bool isPressed(unsigned char input);
		//bool isReleased(unsigned char input);
		//bool isNeutral(unsigned char input);
		//bool isHeldFor(
		//	unsigned char input,
		//	double targetSecondsHeld);
	}
}
