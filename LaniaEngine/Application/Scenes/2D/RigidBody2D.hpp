/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Rigid Body 2D
*
* Component that interfaces with the 2D physics engine in collision and forces.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include <Application/Scenes/2D/Vector2.hpp>
#include <Application/Scenes/2D/Entity2D.hpp>

namespace Lania
{
	typedef struct RigidBody2D
	{
		EntityID entityID;
		double mass_kg;
		double friction_ratio;
		double angularDrag_ratio;
		double gravity_scale;
		double elasticity_ratio;
		double drag_ratio;
		Vector2 angularVelocity_rad_per_s;
		Vector2 velocity_px_per_s;

		RigidBody2D() :
			mass_kg(1.0),
			friction_ratio(1.0),
			angularDrag_ratio(1.0),
			gravity_scale(1.0),
			elasticity_ratio(0.01),
			drag_ratio(1.0)
		{}
	}RigidBody2D;
}
