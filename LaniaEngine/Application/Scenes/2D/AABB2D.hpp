/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Axis Aligned Boundary Box 2D
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <Application/Scenes/2D/Vector2.hpp>

namespace Lania
{
	typedef struct AABB2D
	{
	//	Vector2 min_px;
		Vector2 max_px;
	}AABB2D;
}
