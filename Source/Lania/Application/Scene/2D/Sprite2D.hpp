/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Sprite2D
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include "../../../Utilities/Mathematics/Vector2.hpp"
#include "../../../Utilities/GenericCollections/List.hpp"
#include "Entity2D.hpp"
#include "../Assets/Texture.hpp"
#include "../../../Utilities/GenericCollections/Map.hpp"
#include "../../../Utilities/GenericCollections/String.hpp"

namespace Lania
{
	typedef struct Sprite2D
	{
		enum flipStates
		{
			FLIP_HORIZONTAL = 1 << 0,
			FLIP_VERTICAL = 1 << 1
		};

		EntityID entityID;
		List<Texture> textureFrames;
		uint8_t frameIndex;
		uint8_t alpha;
		uint8_t flip;

		Sprite2D():
			entityID(NO_ENTITY),
			frameIndex(0),
			alpha(255),
			flip(0)
		{}
	}Sprite2D;
}