/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Timing
*
* Defines engine and simulation time data.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

namespace Lania
{
	typedef struct
	{
		double simulation;
		int cycleStart;
		int cycleEnd;
		int cycleDelta;
		int frameDelay;
		int frame;
	}Timing;
}