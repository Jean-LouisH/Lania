/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Rendering
*
* Delegates rendering works to 2D and 3D rendering engines by renderables output.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include <Core/HAL/Output.hpp>
#include <Core/Core.hpp>

namespace Lania
{
	namespace Rendering
	{
		void render(
			Renderables* renderables,
			uint8_t renderer, 
			SDL_Window* window, 
			SDL_Renderer* sdlRenderer);

		namespace SDL2
		{
			void render(Renderables* renderables, SDL_Window* window, SDL_Renderer* sdlRenderer);
			void clearBuffers(SDL_Renderer* sdlRenderer);
		}

		namespace OpenGL33
		{
			void render(Renderables* renderables);
			void clearBuffers();
		}
	}
}