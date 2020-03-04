/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Rectangle
*
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>

namespace Lania
{
	typedef struct Rectangle
	{
		double width;
		double height;

		Rectangle():
			width(0.0),
			height(0.0)
		{}
	}Rectangle;
}
