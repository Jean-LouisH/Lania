/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Entity2D
*
* Component reference points in the 2D scene graph.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <stdint.h>
#include <limits.h>
#include <Application/Scenes/2D/Transform2D.hpp>
#include <Core/DataStructures/Map.hpp>
#include <Application/Scenes/2D/Camera2D.hpp>
#include <Application/Scenes/2D/RigidBody2D.hpp>
#include <Application/Scenes/2D/Sprite.hpp>
#include <Application/Scenes/2D/StaticBody2D.hpp>

using EntityID = uint64_t;

namespace Lania
{
	enum Components
	{
		NONE			= 0,
		CAMERA2D		= 1,
		RIGIDBODY2D		= 1 << 2,
		SPRITE			= 1 << 2,
		STATICBODY2D	= 1 << 3
	};

	typedef struct Entity2D
	{
		Transform2D transform;
		List<EntityID> children;
		EntityID parent;
		uint32_t attachedComponentsFlag; //to determine if searches are necessary

		Entity2D() :
			//Assigned to largest value to represent no parent.
			parent(ULLONG_MAX),
			attachedComponentsFlag(0)
		{}
	}Entity2D;
}
