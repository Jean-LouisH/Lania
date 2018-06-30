/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Renderer SDL
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <SDL_render.h>
#include <Application/Scenes/2D/Scene2D.hpp>

namespace Lania
{
	namespace RendererSDL
	{
		void drawSprites(
			SDL_Renderer* SDLRenderer, 
			SDL_Window* window, 
			List<Scene2D>* scene2Ds);
	}
}
