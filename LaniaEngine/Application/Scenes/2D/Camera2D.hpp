/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Camera 2D
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <Application/Scenes/2D/Rect.hpp>
#include <Application/Scenes/2D/Vector2.hpp>

namespace Lania
{
	typedef struct Camera2D
	{
		Rect viewport;
		double rotation;
	}Camera2D;

}