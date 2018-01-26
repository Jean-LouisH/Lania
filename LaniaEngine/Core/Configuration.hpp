/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Configuration
*
* Initializes the engine data according to the configuration file.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <iostream>

namespace Lania
{
	typedef struct AppConfig
	{
		int windowWidthPixels;
		int windowHeightPixels;
		int targetFPS;
		unsigned char windowFlags;
		std::string mainScene;
		std::string appName;
		AppConfig() :
			windowWidthPixels(0),
			windowHeightPixels(0),
			targetFPS(0),
			windowFlags(0)
		{}
	}AppConfig;
}

namespace Config
{
	Lania::AppConfig parseInit(char* fileContent);
}
