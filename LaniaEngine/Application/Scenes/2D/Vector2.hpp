/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Vector2
*
* An element of 2D vector space.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>

namespace Lania
{
	typedef struct Vector2
	{
		double x;
		double y;

		double length();
		double direction();
		Vector2 normalized();

		Vector2():
			x(0.0),
			y(0.0)
		{}
	}Vector2;
}
