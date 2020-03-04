/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Physics2D
*
* Processes rigid body components in bulk to simulate physics.
*
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Application/Scene/2D/Scene2D.hpp>
#include <Application/Scene/2D/CollisionEvent2D.hpp>

namespace Lania
{
	namespace Physics2D
	{
		void detectCollisions(
			double simulationTime_ms,
			Vector<DynamicCollisionEvent2D>* dynamicCollisionEvents,
			Vector<StaticCollisionEvent2D>* staticCollisionEvents,
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

		void lockTranslation(
			Entity2D* entities,
			PositionLock2D* positionLocks,
			int positionLockCount);
	}
}