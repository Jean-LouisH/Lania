/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Platform
*
* Contains all the hardware and OS information for the Engine struct.
*
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
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
		uint32_t L1CacheLineSize_B;
		uint32_t systemRAM_MB;
		int batteryLife_pct;
		char* renderingAPIVersion;
		char* OS;

		Platform():
			logicalCoreCount(0),
			L1CacheLineSize_B(0),
			systemRAM_MB(0),
			batteryLife_pct(0),
			renderingAPIVersion(NULL),
			OS(NULL)
		{}
	}Platform;
}
