/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Node2D
*
* Unit of data points in the 2D scene graph
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <Core/DataStructures/List.hpp>
#include <Application/Scenes/2D/Vector2.hpp>
#include <stdint.h>

namespace Lania
{
	typedef struct Node2D
	{
		uint64_t id; //Memory address of the struct composed of this node.
		Node2D* parent;
		List<Node2D*> children;
		Vector2 position;
	}Node2D;
}
