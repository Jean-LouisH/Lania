/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Rigid Body 2D
*
* 2D node that interfaces with the 2D physics engine in collision and forces.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <Application/Scenes/Node.hpp>
#include <Application/Scenes/2D/Vector2.hpp>

namespace Lania
{
	typedef struct RigidBody2D
	{
		Node node;
		double mass;
		double elasticity;
		double rotation;
		Vector2 velocity;
		Vector2 position;
	}RigidBody2D;
}
