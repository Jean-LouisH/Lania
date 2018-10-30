/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Point Lock 2D
*
* Fixes entities to stored locations despite physics operations on them.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Application/Scenes/2D/Entity2D.hpp>

namespace Lania
{
	typedef struct PointLock2D
	{
		EntityID entityID;
		Vector2 point;

		PointLock2D():
			entityID(NO_PARENT)
		{}
	}PointLock2D;
}
