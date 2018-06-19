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

namespace Lania
{
	typedef struct Node
	{
		Node* parent;
		Lania::List<Node*> children;
		int id;
	}Node;
}
