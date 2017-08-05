/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Runtime Data
*
* Contains the working data for the engine runtime.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <string>

using namespace std;

namespace Lania
{
	enum gameStates
	{
		TITLESCREEN,
		GAMEPLAY,
		PAUSED
	};

	typedef struct
	{
		string windowTitle;
		float aspectRatio;
		int windowHeightPixels;
		int windowWidthPixels;
		int frameCount;
		int targetFPS;
		unsigned char state;
		bool isRunning;
	}RuntimeData;
}
