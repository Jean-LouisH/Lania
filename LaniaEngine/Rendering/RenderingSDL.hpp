/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Renderer SDL
*
* Uses SDL's 2D hardware accelerated rendering on Renderable data vectors.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <SDL_render.h>
#include <Core/Output.hpp>
#include <Application/Scenes/2D/Scene2D.hpp>

namespace Lania
{
	namespace Rendering
	{
		namespace SDL
		{
			void buildRenderablesFromSprites(
				List<SDLRenderable>* SDLRenderables,
				List<Scene2D>* scene2Ds,
				SDL_Window* window);
		}
	}
}
