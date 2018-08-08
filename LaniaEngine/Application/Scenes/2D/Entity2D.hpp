/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Entity2D
*
* Component reference points in the 2D scene graph.
* Contains transform data for components that attach to it.
* Can be inherited by other entity2Ds.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include <limits.h>
#include <Constants.hpp>
#include <Definitions.hpp>
#include <Application/Scenes/2D/Transform2D.hpp>

namespace Lania
{
	enum Components
	{
		NONE			= 0,
		CAMERA2D		= 1,
		RIGIDBODY2D		= 1 << 2,
		SPRITE			= 1 << 2,
		STATICBODY2D	= 1 << 3,
		BOXCOLLIDER2D	= 1 << 4
	};

	typedef struct Entity2D
	{
		Transform2D transform;
		List<EntityID> children;
		EntityID parent;
		uint32_t attachedComponentsFlag; //to determine if searches are necessary

		Entity2D() :
			//Assigned to largest value to represent no parent.
			parent(NO_PARENT),
			attachedComponentsFlag(0)
		{}
	}Entity2D;
}
