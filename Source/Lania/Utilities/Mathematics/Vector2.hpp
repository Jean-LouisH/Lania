/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Vector2
*
* An element of 2D vector space.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

namespace Lania
{
	typedef struct Vector2
	{
		double x;
		double y;

		double length();
		double direction();
		Vector2 normalized();
		double dotProduct(Vector2 operand);

		Vector2 operator+=(Vector2 operand);
		Vector2 operator-=(Vector2 operand);
		Vector2 operator*=(double scale);

		Vector2():
			x(0.0),
			y(0.0)
		{}
	}Vector2;
}
