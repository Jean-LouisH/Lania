/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Rect
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <stdint.h>

namespace Lania
{
	typedef struct Rect
	{
		uint16_t width;
		uint16_t height;

		Rect():
			width(0),
			height(0)
		{}
	}Rect;
}
