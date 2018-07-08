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

#include <stdint.h>
#include <Application/Scenes/2D/AABB2D.hpp>
#include <Application/Scenes/2D/Rect.hpp>
#include <Application/Scenes/2D/Vector2.hpp>
#include <Application/Scenes/2D/Entity2D.hpp>

namespace Lania
{
	typedef struct Camera2D
	{
		int64_t entityID;
		Rect viewport_px;
		uint64_t entityFollowed_id;
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
			scrollTargetSpeed_px_per_s(0.0),
			zoomTargetSpeed_px_per_s(0.0),
			isRotatingWithEntity(false),
			followX(false),
			followY(false),
			current(false)
		{}
	}Camera2D;

}