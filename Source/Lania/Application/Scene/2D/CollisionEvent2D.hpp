/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Collision Event 2D
*
* Records collisions to be processed in physics.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "CollisionNode2D.hpp"

namespace Lania
{
	typedef struct StaticCollisionEvent2D
	{
		EntityID first;
		EntityID second;
		double timestamp_ms;

		StaticCollisionEvent2D():
			first(NO_ENTITY),
			second(NO_ENTITY),
			timestamp_ms(0.0)
		{}
	}StaticCollisionEvent2D;

	typedef struct DynamicCollisionEvent2D
	{
		CollisionNode2D first;
		CollisionNode2D second;
		ComponentListIndex firstRigidBodyIndex;
		double attackAngle;
		double timestamp_ms;

		DynamicCollisionEvent2D():
			firstRigidBodyIndex(0),
			attackAngle(0.0),
			timestamp_ms(0.0)
		{}
	}DynamicCollisionEvent2D;
}