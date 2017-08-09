/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Engine Configuration
*
* Initializes the engine runtime states according to the configuration file "LaniaConfig.cfg"
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <string>

using namespace std;

namespace Lania
{
	class EngineConfiguration
	{
	private:
	public:
		string windowTitle;
		int resolutionHeightPixels;
		int resolutionWidthPixels;
		int targetFPS;
		double FPSRefreshDelay;
		//glContext
		int windowXPosition;
		int windowYPosition;
		//glBufferDepth
		//SDL_swap_interval
		void parseConfigFile(char* fileData);
	};
}
	