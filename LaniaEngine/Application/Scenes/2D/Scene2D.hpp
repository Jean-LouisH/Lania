/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Scene 2D 
*
* Contains components and entities that are processed exclusively
* by 2D algorithms. Is layered with 3D scenes in the Scene struct.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <map>
#include <stdint.h>
#include <Definitions.hpp>
#include <Core/Input.hpp>
#include <Core/DataStructures/List.hpp>
#include <Core/DataStructures/Map.hpp>
#include "BoxCollider2D.hpp"
#include "Camera2D.hpp"
#include "Entity2D.hpp"
#include "RigidBody2D.hpp"
#include "Sprite2D.hpp"
#include "PointLock2D.hpp"

namespace Lania
{
	typedef struct Scene2D
	{
		//Entities listed and layered by ID numbers
		List<Entity2D> entities;

		//Active component existence-based processing lists
		//Ordered by entity layer, but not necessarily matched to IDs
		//Components contain parent entity IDs
		List<Sprite2D> activeSprites;
		List<Camera2D> activeCameras;
		List<RigidBody2D> activeRigidBodies;
		List<BoxCollider2D> activeBoxColliders;
		List<PointLock2D> pointLocks;

		//Inactive storage lists
		//No ordering enforced as long as components maintain parent entity IDs
		List<Sprite2D> inactiveSprites;
		List<Camera2D> inactiveCameras;
		List<RigidBody2D> inactiveRigidBodies;

		//Stores current camera list position to prevent repetitive searches
		ComponentListIndex currentCameraIndex;
	}Scene2D;
}
