/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* SDL Renderable
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <SDL_render.h>

namespace Lania
{
	typedef struct SDLRenderable
	{
		SDL_Texture* texture;
		SDL_Rect textureRect;
		SDL_Rect renderingRect;
		double rotation;
		SDL_RendererFlip flip;
	}SDLRenderable;
}
