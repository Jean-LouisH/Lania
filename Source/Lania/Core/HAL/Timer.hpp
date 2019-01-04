/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Timing
*
* Defines engine execution and simulation timers for performance
* monitoring and balance.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <chrono>
#include <stdint.h>

namespace Lania
{
	class ExecutionTimer
	{
	private:
		uint64_t delta_ns;
		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> end;
	public:
		uint64_t getDelta_ns();
		void setStart();
		void setEnd();
		ExecutionTimer() :
			delta_ns(0)
		{}
	};

	typedef struct Timer
	{
		ExecutionTimer process;
		ExecutionTimer frame;
		ExecutionTimer input;
		ExecutionTimer logic;
		ExecutionTimer compute;
		ExecutionTimer output;
		ExecutionTimer sleep;
		ExecutionTimer benchmark;
		ExecutionTimer FPS;
		ExecutionTimer run;
		ExecutionTimer shutdown;
		double simulation_ms;
		uint64_t lag_ms;
		Timer() :
			simulation_ms(0.0),
			lag_ms(0) 
		{}
	}Timing;
}
