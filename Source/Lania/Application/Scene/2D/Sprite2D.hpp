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
#include "../../../Utilities/DataStructures/Vector.hpp"
#include "Entity2D.hpp"
#include "../Assets/Texture.hpp"
#include "../../../Utilities/DataStructures/Map.hpp"
#include "../../../Utilities/DataStructures/String.hpp"

namespace Lania
{
	enum flipStates
	{
		FLIP_HORIZONTAL = 1 << 0,
		FLIP_VERTICAL = 1 << 1
	};

	typedef struct Sprite2D
	{
		EntityID entityID;
		Vector<Texture> textureFrames;
		uint8_t frameIndex;
		uint8_t alpha;
		uint8_t flip;

		Sprite2D():
			entityID(NO_PARENT),
			frameIndex(0),
			alpha(255),
			flip(0)
		{}
	}Sprite2D;
}