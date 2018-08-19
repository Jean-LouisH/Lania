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
#include <Application/Scenes/2D/CollisionEvent2D.hpp>

namespace Lania
{
	namespace Physics2D
	{
		void detectCollisions(
			double simulationTime_ms,
			List<DynamicCollisionEvent2D>* dynamicCollisionEvents,
			List<StaticCollisionEvent2D>* staticCollisionEvents,
			Entity2D* entities,
			RigidBody2D* rigidBodies,
			int rigidBodyCount,
			BoxCollider2D* boxColliders,
			int boxColliderCount);

		void handleCollisions(
			DynamicCollisionEvent2D* dynamicCollisionEvents,
			int dynamicCollisionEventCount,
			RigidBody2D* rigidBodies);

		void decelerate(
			RigidBody2D* rigidBodies,
			int rigidBodyCount);

		void force(
			RigidBody2D* rigidBodies,
			int rigidBodyCount);

		void gravitate(
			RigidBody2D* rigidBodies,
			int rigidBodyCount);

		void displace(
			Entity2D* entities,
			RigidBody2D* rigidBodies,
			int rigidBodyCount);

		void lock(
			Entity2D* entities,
			PointLock2D* pointLocks,
			int pointLockCount);
	}
}