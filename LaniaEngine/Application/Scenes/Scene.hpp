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
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <Core/DataStructures/Map.hpp>
#include <stdint.h>
#include <Core/Input.hpp>
#include "2D/Scene2D.hpp"
#include <Definitions.hpp>
#include <Core/DataStructures/List.hpp>
#include <Core/DataStructures/String.hpp>

namespace Lania
{
	enum LayerTypes
	{
		SUBSCENE_2D,
		SUBSCENE_3D
	};

	typedef struct Scene
	{
		List<Scene2D> subscenes2D;
		List<LayerType> layers;
		Multimap<String, SDL_Keycode> actionInputMaps;
		Multimap<SDL_Keycode, int> keyScriptMaps;
	}Scene;
}
