/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Timing
*
* Defines engine and application time data.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <chrono>
#include <stdint.h>

namespace Lania
{
	typedef struct ExecutionTimer
	{
		uint64_t delta;
		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> end;
		void setStart();
		void setEnd();
		ExecutionTimer() :
			delta(0)
		{}
	}ExecutionTimer;

	typedef struct Timer
	{
		ExecutionTimer cycle;
		ExecutionTimer frame;
		ExecutionTimer input;
		ExecutionTimer script;
		ExecutionTimer compute;
		ExecutionTimer output;
		ExecutionTimer FPS;
		double simulation;
		uint64_t lag;
		Timer() :
			simulation(0.0),
			lag(0) 
		{}
	}Timing;
}
