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
*/

#pragma once

#include <SDL.h>
#include <Input/Keyboard.hpp>
#include <Core/DataStructures/List.hpp>

namespace Lania
{
	enum sizes
	{
		KEY_BUFFER_SIZE = 128,
	};

	typedef struct Input
	{
		List<Key::KeyEvent> keyEvents;
		List<SDL_GameController*> gameControllers;
	}Input;
}
