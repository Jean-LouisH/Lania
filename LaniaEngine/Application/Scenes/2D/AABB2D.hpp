/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Axis Aligned Bounding Box 2D
*
* For defining regions in 2D for collision detection and spatial limits on cameras.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <Application/Scenes/2D/Vector2.hpp>

namespace Lania
{
	typedef struct AABB2D
	{
		Vector2 min_px;
		Vector2 max_px;
	}AABB2D;
}
