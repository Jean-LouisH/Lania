/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Collision Event 2D
*
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <Application/Scenes/2D/CollisionNode2D.hpp>

namespace Lania
{
	typedef struct StaticCollisionEvent2D
	{
		EntityID first;
		EntityID second;
		double timestamp_ms;

		StaticCollisionEvent2D():
			first(NO_PARENT),
			second(NO_PARENT),
			timestamp_ms(0.0)
		{}
	}StaticCollisionEvent2D;

	typedef struct DynamicCollisionEvent2D
	{
		CollisionNode2D first;
		CollisionNode2D second;
		double attackAngle;
		double timestamp_ms;

		DynamicCollisionEvent2D():
			attackAngle(0.0),
			timestamp_ms(0.0)
		{}
	}DynamicCollisionEvent2D;
}