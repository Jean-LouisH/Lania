/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Scene
*
* Creates, manages and deletes data structures that define active scenes.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <map>
#include <stdint.h>
#include <Core/Input.hpp>

namespace Lania
{
	typedef struct Scene
	{
		uint8_t dimension;
		std::multimap<SDL_Keycode, int> keyMaps;
	}Scene;
}
