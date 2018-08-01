/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Box Collider 2D
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <stdint.h>
#include <Application/Scenes/2D/AABB2D.hpp>
#include <Application/Scenes/2D/Entity2D.hpp>

namespace Lania
{
	typedef struct BoxCollider2D
	{
		EntityID entityID;
		AABB2D aabb;
	}BoxCollider2D;
}
