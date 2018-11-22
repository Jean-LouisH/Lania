/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Sprite2D
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include <Core/DataStructures/List.hpp>
#include <Application/Scenes/2D/Vector2.hpp>
#include <Application/Scenes/2D/Entity2D.hpp>
#include <Application/Scenes/Texture.hpp>

namespace Lania
{
	typedef struct Sprite2D
	{
		EntityID entityID;
		List<Texture> textureFrames;
		uint8_t frameIndex;
		uint8_t alpha;
		bool flip;

		Sprite2D():
			entityID(NO_PARENT),
			frameIndex(0),
			alpha(255),
			flip(false)
		{}
	}Sprite2D;
}