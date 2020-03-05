/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Profiler
*
* Defines engine execution and simulation timers for performance
* monitoring and balance.
*
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include "HiResTimer.hpp"

namespace Lania
{
	class Profiler
	{
	public:
		HiResTimer process;
		HiResTimer frame;
		HiResTimer input;
		HiResTimer logic;
		HiResTimer compute;
		HiResTimer output;
		HiResTimer sleep;
		HiResTimer benchmark;
		HiResTimer FPS;
		HiResTimer run;
		HiResTimer debug;
		uint64_t lag_ms;
		Profiler() :
			lag_ms(0) 
		{}
	};
}
