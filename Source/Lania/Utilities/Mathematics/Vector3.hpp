/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Vector3
*
* An element of 3D vector space.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

namespace Lania
{
	typedef struct Vector3
	{
		double x;
		double y;
		double z;

		Vector3() :
			x(0.0),
			y(0.0),
			z(0.0)
		{}
	}Vector3;
}
