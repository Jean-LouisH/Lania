/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Scene 2D 
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <map>
#include <stdint.h>
#include <Core/Input.hpp>
#include <Core/DataStructures/List.hpp>
#include "Camera2D.hpp"
#include "Entity2D.hpp"
#include "RigidBody2D.hpp"
#include "Sprite.hpp"
#include "StaticBody2D.hpp"

namespace Lania
{
	typedef struct Scene2D
	{
		List<Camera2D> cameras;
		List<Entity2D> entities;
		List<RigidBody2D> rigidBodies;
		List<Sprite> sprites;
		List<StaticBody2D> staticBodies;
	}Scene2D;
}
