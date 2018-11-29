/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Transform 2D
*
* Position, rotation and scale of entities.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "Vector2.hpp"

namespace Lania
{
	typedef struct Transform2D
	{
		Vector2 position_px;
		double rotation_rad;
		Vector2 scale;

		Transform2D() : 
			rotation_rad(0.0)
		{
			this->scale.x = 1;
			this->scale.y = 1;
		}
	}Transform2D;
}
