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
#include <Application/Scenes/2D/Node2D.hpp>

typedef struct
{
	Node2D node;
	Rect viewport;
	double rotation;
}Camera_2D;
