/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Output
*
* Defines all means of output for the engine.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <Core/DataStructures/List.hpp>
#include <Rendering/SDLRenderable.hpp>

namespace Lania
{
	typedef struct Output
	{
		List<SDLRenderable> SDLRenderables;
	}Output;
}
