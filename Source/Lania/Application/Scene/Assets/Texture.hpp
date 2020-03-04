/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Texture
*
* Contains texture size and memory for hardware acceleration.
*
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include "../../../Utilities/Mathematics/Mathematics.hpp"
#include "../../../Utilities/GenericCollections/String.hpp"
#include <SDL_image.h>
#include <SDL.h>

namespace Lania
{
	class Texture
	{
	private:
		SDL_Surface* surface;
	public:
		SDL_Surface* getSDLSurface();
		uint8_t* getData();
		uint64_t getSize();
		Rectangle getDimensions();
		double getWidth();
		double getHeight();
		uint8_t getBytesPerPixel();
		void load(String filePath);
		void unload();
		~Texture();
	};
}