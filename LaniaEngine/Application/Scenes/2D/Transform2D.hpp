/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Transform 2D
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <Application/Scenes/2D/Vector2.hpp>

namespace Lania
{
	typedef struct Transform2D
	{
		Vector2 position;
		Vector2 rotation;
		Vector2 scale;
	}Transform2D;
}
