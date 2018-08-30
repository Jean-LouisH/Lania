/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Sprite2D
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <SDL_render.h>
#include <stdint.h>
#include <Application/Scenes/2D/Vector2.hpp>
#include <Application/Scenes/2D/Entity2D.hpp>
#include <Application/Scenes/Texture.hpp>

namespace Lania
{
	typedef struct Sprite2D
	{
		EntityID entityID;
		Texture texture;
		uint8_t alpha;
		SDL_RendererFlip flip;

		Sprite2D():
			entityID(NO_PARENT),
			alpha(255),
			flip(SDL_FLIP_NONE)
		{}
	}Sprite2D;
}