/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Transform 3D
*
* Position, rotation and scale of entities in 3-space.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "Vector3.hpp"

namespace Lania
{
	typedef struct Transform3D
	{
		Vector3 position_m;
		Vector3 rotation_rad;
		Vector3 scale;

		Transform3D()
		{
			this->scale.x = 1;
			this->scale.y = 1;
			this->scale.z = 1;
		}
	}Transform3D;
}
