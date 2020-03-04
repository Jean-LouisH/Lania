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
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include "ExecutionTimer.hpp"

namespace Lania
{
	class EngineTimers
	{
	public:
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
		ExecutionTimer debug;
		uint64_t lag_ms;
		EngineTimers() :
			lag_ms(0) 
		{}
	};
}
