/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Input
*
* Defines all means of input in the engine.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <SDL.h>
#include "SDL_stdinc.h"
#include "SDL_keycode.h"
#include <Core/DataStructures/List.hpp>
#include <Core/DataStructures/Map.hpp>

namespace Lania
{
	typedef struct
	{
		Uint16 mod;
		Uint32 timestamp_ms;
	}KeyEvent;

	typedef struct
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
