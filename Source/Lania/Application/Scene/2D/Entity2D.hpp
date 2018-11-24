/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Entity2D
*
* Component reference points in the 2D scene graph.
* Contains transform data for components that attach to it.
* Can be inherited by other entity2Ds.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include <limits.h>
#include <Constants.hpp>
#include <Definitions.hpp>
#include <Application/Scenes/2D/Transform2D.hpp>
#include <Core/DataStructures/Set.hpp>
#include <SDL_mixer.h>

namespace Lania
{
	enum Components
	{
		NO_COMPONENT,
		CAMERA_2D,
		RIGID_BODY_2D,
		SPRITE_2D,
		BOX_COLLIDER_2D,
		POINT_LOCK_2D,
	};

	typedef struct Entity2D
	{
		Transform2D transform;
		List<EntityID> children;
		EntityID parent;
		Map<ComponentType, ComponentListIndex> components;

		Entity2D() :
			parent(NO_PARENT)
		{}
	}Entity2D;
}
