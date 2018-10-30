/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Camera 2D
*
* A component used by 2D renderers to render visible sections of a
* scene by position, rotation and scale.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include <Application/Scenes/2D/AABB2D.hpp>
#include <Application/Scenes/2D/Rect.hpp>
#include <Application/Scenes/2D/Vector2.hpp>
#include <Application/Scenes/2D/Entity2D.hpp>

namespace Lania
{
	typedef struct Camera2D
	{
		EntityID entityID;
		Rect viewport_px;
		EntityID entityFollowed_id;
		Vector2 scrollTarget_px;
		Vector2 offset_px;
		Rect zoomTarget_px;
		AABB2D limits;
		double scrollTargetSpeed_px_per_s;
		double zoomTargetSpeed_px_per_s;
		bool isRotatingWithEntity;
		bool followX;
		bool followY;
		bool current;

		Camera2D() :
			entityID(NO_PARENT),
			entityFollowed_id(NO_PARENT),
			scrollTargetSpeed_px_per_s(0.0),
			zoomTargetSpeed_px_per_s(0.0),
			isRotatingWithEntity(false),
			followX(false),
			followY(false),
			current(false)
		{}
	}Camera2D;

}