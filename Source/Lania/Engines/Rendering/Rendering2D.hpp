/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Rendering2D
*
* Rendering sub engine for 2D graphics.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Core/HAL/Renderables.hpp>

namespace Lania
{
	namespace Rendering2D
	{
		namespace OpenGL
		{
			void drawSprites(
				Sprite2DRenderable* sprites2D, 
				int spriteCount,
				Camera2DRenderable* currentCamera2D);
		}
	}
}