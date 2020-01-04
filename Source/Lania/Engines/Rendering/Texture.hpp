#pragma once

#include <SDL_video.h>
#include "Rect.hpp"

namespace SDLSubEngines
{
	typedef struct Texture
	{
		SDL_Texture* data;
		Rect pixels;
	}Texture;
}