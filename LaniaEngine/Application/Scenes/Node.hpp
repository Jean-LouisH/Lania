/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Node
*
* Unit of data points in the scene graph
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <Core/DataStructures/List.hpp>
#include <stdint.h>

namespace Lania
{
	typedef struct Node
	{
		uint64_t id; //Memory address of the struct composed of this node.
		Node* parent;
		List<Node*> children;
	}Node;
}
