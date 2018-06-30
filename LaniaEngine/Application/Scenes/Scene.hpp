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

#include <Core/DataStructures/Map.hpp>
#include <stdint.h>
#include <Core/Input.hpp>
#include "2D/Scene2D.hpp"
#include <Core/DataStructures/List.hpp>
#include <Core/DataStructures/String.hpp>

namespace Lania
{
	typedef struct Scene
	{
		List<Scene2D> subscenes2D;
		List<uint8_t> zIndices;
		Multimap<String, SDL_Keycode> actionInputMaps;
		Multimap<SDL_Keycode, int> keyScriptMaps;
	}Scene;
}
