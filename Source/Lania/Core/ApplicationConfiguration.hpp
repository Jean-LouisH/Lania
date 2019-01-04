/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Application Configuration
*
* Contains engine and application data according to the configuration file.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include <Utilities/DataStructures/String.hpp>

namespace Lania
{
	typedef struct AppConfig
	{
		uint16_t windowWidth_px;
		uint16_t windowHeight_px;
		uint16_t targetFPS;
		uint32_t windowFlags;
		String mainScene;
		String appName;

		AppConfig() :
			windowWidth_px(0),
			windowHeight_px(0),
			targetFPS(0),
			windowFlags(0)
		{}
	}AppConfig;
}