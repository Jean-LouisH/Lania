/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Scene 2D 
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <map>
#include <stdint.h>
#include <Core/Input.hpp>
#include <Core/DataStructures/List.hpp>
#include <Core/DataStructures/Map.hpp>
#include "Camera2D.hpp"
#include "Entity2D.hpp"
#include "RigidBody2D.hpp"
#include "Sprite.hpp"
#include "StaticBody2D.hpp"

using ComponentListIndex = uint64_t;

namespace Lania
{
	typedef struct Scene2D
	{
		//Entities listed and layered by ID numbers
		List<Entity2D> entities;

		//Active component existence-based processing lists
		//Ordered by entity layer, but not necessarily matched to IDs
		//Components contain parent entity IDs
		List<Sprite> activeSprites;
		List<Camera2D> activeCameras;
		List<RigidBody2D> activeRigidBodies;
		List<StaticBody2D> activeStaticBodies;

		//Inactive storage lists
		//No ordering enforced as long as components maintain parent entity IDs
		List<Sprite> inactiveSprites;
		List<Camera2D> inactiveCameras;
		List<RigidBody2D> inactiveRigidBodies;
		List<StaticBody2D> inactiveStaticBodies;

		//Stores current camera list position to prevent repetitive searches
		ComponentListIndex currentCameraIndex;
	}Scene2D;
}
