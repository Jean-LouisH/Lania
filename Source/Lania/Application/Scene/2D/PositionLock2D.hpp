/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Poisition Lock 2D
*
* Fixes entities to stored locations despite physics operations on them.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "Entity2D.hpp"

namespace Lania
{
	typedef struct PositionLock2D
	{
		EntityID entityID;
		Vector2 point;

		PositionLock2D():
			entityID(NO_ENTITY)
		{}
	}PositionLock2D;
}
