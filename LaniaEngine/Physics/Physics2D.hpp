/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Physics2D
*
* Processes rigid body components in bulk to simulate physics.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <Application/Scenes/2D/Scene2D.hpp>

namespace Lania
{
	namespace Physics2D
	{
		void detectCollisions(
			Entity2D* entities,
			BoxCollider2D* boxColliders,
			int boxColliderCount);
		void decelerate(
			RigidBody2D* rigidBodies,
			int rigidBodyCount);
		void gravitate(
			RigidBody2D* rigidBodies,
			int rigidBodyCount);
		void displace(Entity2D* entities,
			RigidBody2D* rigidBodies,
			int rigidBodyCount);
		void lock(
			Entity2D* entities,
			PointLock2D* pointLocks,
			int pointLockCount);
	}
}