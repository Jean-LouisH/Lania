/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Circle Collider
*
* Defines a region for collision based on a radius.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "Entity2D.hpp"

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
