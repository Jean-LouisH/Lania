/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Timing
*
* Defines engine and simulation time data.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <chrono>

namespace Lania
{
	typedef struct Execution
	{
		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> end;
		long long int delta;
		void setStart();
		void setEnd();
		Execution() :
			delta(0)
		{}
	}Execution;

	typedef struct Timing
	{
		Execution cycle;
		Execution frame;
		Execution input;
		Execution script;
		Execution compute;
		Execution output;
		double simulation;
		int lag;
		Timing() :
			simulation(0.0),
			lag(0) 
		{}
	}Timing;
}