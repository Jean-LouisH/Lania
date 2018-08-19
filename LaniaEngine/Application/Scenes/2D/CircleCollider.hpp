/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Circle Collider
*
* Defines a region for collision based on a radius.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include <Application/Scenes/2D/Entity2D.hpp>

namespace Lania
{
	typedef struct CircleCollider
	{
		EntityID entityID;
		double radius_px;

		CircleCollider():
			entityID(NO_PARENT),
			radius_px(0.0)
		{}
	}CircleCollider;
}
