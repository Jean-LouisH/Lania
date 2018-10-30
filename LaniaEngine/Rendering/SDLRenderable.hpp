/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* SDL Renderable
*
* Contains all data necessary for SDL_RenderCopyEx.
* Is available to the rest of the decision procedure
* in the engine for image acquisition and editing.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
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
