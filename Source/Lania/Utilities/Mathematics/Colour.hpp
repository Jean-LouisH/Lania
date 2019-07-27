/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Colour
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include <string>

namespace Lania
{
	typedef struct Colour
	{
		double red;
		double blue;
		double green;
		double alpha;
		Colour();
		Colour(std::string hex);
	}Colour;
}