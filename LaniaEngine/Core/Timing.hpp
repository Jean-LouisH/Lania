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
	typedef struct Timing
	{
		double simulation;
		int cycleStart;
		int cycleEnd;
		int cycleDelta;
		int frameDelay;
		int frame;
		int lag;
		Timing() :
			simulation(0.0),
			cycleStart(0),
			cycleEnd(0),
			cycleDelta(0),
			frameDelay(0),
			frame(0),
			lag(0) {}
	}Timing;
}