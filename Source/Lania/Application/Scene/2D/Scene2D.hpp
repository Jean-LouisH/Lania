/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Scene 2D 
*
* Contains components and entities that are processed exclusively
* by 2D algorithms. Is layered with 3D scenes in the Scene struct.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "../../../Utilities/Definitions/Aliases.hpp"
#include "../../../Utilities/DataStructures/Vector.hpp"
#include "../../../Utilities/DataStructures/Map.hpp"
#include "../../../Utilities/DataStructures/String.hpp"

#include "AABB2D.hpp"
#include "BoxCollider2D.hpp"
#include "Camera2D.hpp"
#include "CircleCollider.hpp"
#include "CollisionEvent2D.hpp"
#include "CollisionNode2D.hpp"
#include "ConstantDirectionalForce2D.hpp"
#include "ConstantPointForce2D.hpp"
#include "Entity2D.hpp"
#include "PositionLock2D.hpp"
#include "RigidBody2D.hpp"
#include "Sprite2D.hpp"
#include "TriggerZone2D.hpp"

namespace Lania
{
	typedef struct Scene2D
	{
		//Entities listed and layered by ID numbers
		Vector<Entity2D> entities;

		Map<String, EntityID> entityNameRegistry;
		Vector<DynamicCollisionEvent2D> dynamicCollisionEvents;
		Vector<StaticCollisionEvent2D> staticCollisionEvents;

		//Active component existence-based processing lists
		//Ordered by entity layer, but not necessarily matched to IDs
		//Components contain parent entity IDs
		Vector<Sprite2D> activeSprites;
		Vector<Camera2D> activeCameras;
		Vector<RigidBody2D> activeRigidBodies;
		Vector<BoxCollider2D> activeBoxColliders;
		Vector<PositionLock2D> pointLocks;

		//Inactive storage lists
		//No ordering enforced as long as components maintain parent entity IDs
		Vector<Sprite2D> inactiveSprites;
		Vector<Camera2D> inactiveCameras;
		Vector<RigidBody2D> inactiveRigidBodies;

		//Stores current camera list position to prevent repetitive searches
		ComponentListIndex currentCameraIndex;

		Scene2D()
		{
			//The universal, empty parent entity used for reference
			//in recursive algorithms on child entities.
			Entity2D dummy;
			this->entities.push_back(dummy);

			//Allocates memory on initialization to prevent frame stutter from
			//first detected collisions.
			this->dynamicCollisionEvents.reserve(sizeof(DynamicCollisionEvent2D));
			this->staticCollisionEvents.reserve(sizeof(StaticCollisionEvent2D));
		}
	}Scene2D;
}
