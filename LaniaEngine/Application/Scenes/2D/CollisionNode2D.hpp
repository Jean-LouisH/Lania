/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Collision Node 2D
*
* Contains necessary data to compute collisions.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <Application/Scenes/2D/Entity2D.hpp>

namespace Lania
{
	typedef struct CollisionNode2D
	{
		EntityID entityID;
		Vector2 velocity_px_per_s;
		double mass_kg;
		double rotation_rad;
		double elasticity_ratio;
		ComponentType collider;

		CollisionNode2D():
			entityID(NO_PARENT),
			mass_kg(0.0),
			rotation_rad(0.0),
			elasticity_ratio(0.0),
			collider(NO_COMPONENT)
		{}
	}CollisionNode2D;
}