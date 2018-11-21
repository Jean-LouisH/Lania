/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Box Collider 2D
*
* The component form of the axis aligned bounding box 2D 
* specifically used for collision detection.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include <Application/Scenes/2D/AABB2D.hpp>
#include <Application/Scenes/2D/Entity2D.hpp>

namespace Lania
{
	typedef struct BoxCollider2D
	{
		EntityID entityID;
		AABB2D aabb;
		BoxCollider2D():
			entityID(NO_PARENT)
		{}
	}BoxCollider2D;
}