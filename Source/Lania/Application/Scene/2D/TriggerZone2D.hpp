/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Trigger Zone 2D 
*
* The component form of the axis aligned bounding box 2D
* specifically used for detection of entered bodies.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "../../../Utilities/Mathematics/AABB2D.hpp"
#include "Entity2D.hpp"

namespace Lania
{
	typedef struct TriggerZone2D
	{
		EntityID entityID;
		AABB2D aabb;
		TriggerZone2D() :
			entityID(NO_ENTITY)
		{}
	}TriggerZone2D;
}