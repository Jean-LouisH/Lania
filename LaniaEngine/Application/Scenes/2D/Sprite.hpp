/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Sprite
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <SDL_render.h>
#include <Application/Scenes/Node.hpp>
#include <Application/Scenes/2D/Rect.hpp>
#include <Application/Scenes/2D/Vector2.hpp>

namespace Lania
{
	typedef struct
	{
		Node node;
		SDL_Texture* texture;
		Rect pixels;
		Vector2 position;
		bool xFlip;
		bool yFlip;
	}Sprite;
}