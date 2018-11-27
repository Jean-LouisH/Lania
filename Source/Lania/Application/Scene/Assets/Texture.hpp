/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Texture
*
* Contains texture size and memory for hardware acceleration.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include "../../../Utilities/Mathematics/Rect.hpp"

namespace Lania
{
	typedef struct Texture
	{
		uint8_t* data;
		uint64_t size;
		Rect pixels;
	}Texture;
}