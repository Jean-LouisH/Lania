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
#include "../../../Utilities/GenericCollections/List.hpp"
#include "../../../Utilities/GenericCollections/Map.hpp"
#include "../../../Utilities/GenericCollections/String.hpp"

#include "AudioListener2D.hpp"
#include "AudioSource2D.hpp"
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
		List<Entity2D> entities;

		Map<String, EntityID> entityNameRegistry;
		List<DynamicCollisionEvent2D> dynamicCollisionEvents;
		List<StaticCollisionEvent2D> staticCollisionEvents;

		//Active component existence-based processing lists
		//Ordered by entity layer, but not necessarily matched to IDs
		//Components contain parent entity IDs
		List<Sprite2D> activeSprites;
		List<Camera2D> activeCameras;
		List<RigidBody2D> activeRigidBodies;
		List<BoxCollider2D> activeBoxColliders;
		List<PositionLock2D> pointLocks;
		List<AudioSource2D> activeAudioSources;
		List<AudioListener2D> activeAudioListeners;

		//Inactive storage lists
		//No ordering enforced as long as components maintain parent entity IDs
		List<Sprite2D> inactiveSprites;
		List<Camera2D> inactiveCameras;
		List<RigidBody2D> inactiveRigidBodies;
		List<AudioSource2D> inactiveAudioSources;
		List<AudioListener2D> inactiveAudioListeners;

		//Stores current camera list position to prevent repetitive searches
		ComponentListIndex currentCameraIndex;

		Scene2D()
		{
			//The universal, empty parent entity used for reference
			//in recursive algorithms on child entities.
			Entity2D scene2DEntity;
			this->entities.push_back(scene2DEntity);

			//Allocates memory on initialization to prevent frame stutter from
			//first detected collisions.
			this->dynamicCollisionEvents.reserve(sizeof(DynamicCollisionEvent2D));
			this->staticCollisionEvents.reserve(sizeof(StaticCollisionEvent2D));
		}
	}Scene2D;
}
