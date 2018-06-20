/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Static Body 2D
*
* 2D node that interfaces with direct manipulation and scripting.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <Application/Scenes/Node.hpp>
#include <Application/Scenes/2D/Vector2.hpp>

namespace Lania
{
	typedef struct StaticBody2D
	{
		Node node;
		double rotation;
		Vector2 position;
	}StaticBody2D;
}