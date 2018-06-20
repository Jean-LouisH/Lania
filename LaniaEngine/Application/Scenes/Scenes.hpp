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

#include <vector>
#include <map>
#include <Core/Input.hpp>

namespace Lania
{
	typedef struct Scene
	{
		unsigned char dimension;
		std::vector<std::map<SDL_Keycode, std::vector<int>>> keyMaps;
	}Scene;
}
