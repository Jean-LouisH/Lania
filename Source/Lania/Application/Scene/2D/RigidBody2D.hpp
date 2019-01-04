/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Rigid Body 2D
*
* Component that interfaces with the 2D physics engine in collision and forces.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "Entity2D.hpp"
#include "../../../Utilities/Mathematics/Vector2.hpp"

namespace Lania
{
	typedef struct RigidBody2D
	{
		EntityID entityID;
		double mass_kg;
		double friction_ratio;
		double angularDrag_ratio;
		double angularVelocity_rad_per_s;
		double gravity_scale;
		double elasticity_ratio;
		Vector2 drag_ratio;
		Vector2 velocity_px_per_s;

		RigidBody2D() :
			mass_kg(1.0),
			friction_ratio(1.0),
			angularDrag_ratio(1.0),
			angularVelocity_rad_per_s(0.0),
			gravity_scale(1.0),
			elasticity_ratio(0.01)
		{ 
			drag_ratio.x = 0.0001;
			drag_ratio.y = 1.0; 
		}
	}RigidBody2D;
}
