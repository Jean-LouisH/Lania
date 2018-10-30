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

#include <SDL_video.h>
#include <Application/Scenes/2D/Rect.hpp>

namespace Lania
{
	typedef struct Texture
	{
		SDL_Texture* data;
		Rect pixels;
	}Texture;
}