/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Input
*
* Defines all means of input in the engine.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <SDL.h>
#include "SDL_stdinc.h"
#include "SDL_keycode.h"
#include "../../Utilities/DataStructures/List.hpp"
#include "../../Utilities/DataStructures/Map.hpp"

namespace Lania
{
	typedef struct KeyEvent
	{
		Uint16 mod;
		Uint32 timestamp_ms;
	}KeyEvent;

	typedef struct MouseState
	{
		Uint32 type;
		Uint8 clicks;
		Sint32 x;
		Sint32 y;
		Sint32 xrel;
		Sint32 yrel;
		Sint32 xScroll;
		Sint32 yScroll;
		Uint32 direction;
		Uint8 button;
		Uint8 buttonState;
		Uint32 motionState;
		Uint32 timestamp_ms;
		Uint32 windowID;

		MouseState():
			type(0),
			clicks(0),
			x(0),
			y(0),
			xrel(0),
			yrel(0),
			xScroll(0),
			yScroll(0),
			direction(0),
			button(0),
			buttonState(0),
			motionState(0),
			timestamp_ms(0),
			windowID(0)
		{}
	}MouseState;

	typedef struct Input
	{
		Map<SDL_Keycode, KeyEvent> pressedKeys;
		Map<SDL_Keycode, KeyEvent> releasedKeys;
		MouseState mouse;
		List<SDL_GameController*> gameControllers;
		List<SDL_Haptic*> haptics;
		List<SDL_HapticEffect> hapticEffects;
	}Input;
}
