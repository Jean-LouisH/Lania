/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Platform
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <SDL.h>
#include <stdint.h>

namespace Lania
{
	typedef struct Platform
	{
		SDL_DisplayMode SDLDisplayMode;
		uint8_t logicalCoreCount;
		uint32_t L1CacheSize_B;
		uint32_t systemRAM_MB;
		int batteryLife_pct;
		char* renderingAPIVersion;
		char* OS;

		Platform():
			logicalCoreCount(0),
			L1CacheSize_B(0),
			systemRAM_MB(0),
			batteryLife_pct(NULL),
			renderingAPIVersion(NULL),
			OS(NULL)
		{}
	}Platform;
}
