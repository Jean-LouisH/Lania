#pragma once

#include "Rect.hpp"
#include "Transform2D.hpp"

namespace SDLSubEngines
{
	typedef struct Camera2D
	{
		Transform2D transform;
		Rect viewport_px;
	}Camera2D;
}