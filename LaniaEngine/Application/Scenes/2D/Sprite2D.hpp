/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Sprite2D
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <SDL_render.h>
#include <stdint.h>
#include <Application/Scenes/2D/Rect.hpp>
#include <Application/Scenes/2D/Vector2.hpp>
#include <Application/Scenes/2D/Entity2D.hpp>

namespace Lania
{
	typedef struct Sprite2D
	{
		EntityID entityID;
		SDL_Texture* texture;
		uint8_t alpha;
		Rect pixels;
		SDL_RendererFlip flip;

		Sprite2D():
			flip (SDL_FLIP_NONE)
		{}
	}Sprite2D;
}