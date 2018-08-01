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
#include <Core/Output.hpp>
#include <Application/Scenes/2D/Scene2D.hpp>

namespace Lania
{
	namespace RendererSDL
	{
		void buildRenderablesFromSprites(
			List<SDLRenderable>* SDLRenderables,
			List<Scene2D>* scene2Ds, 
			SDL_Window* window);
	}
}
