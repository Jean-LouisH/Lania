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
		long long int delta;
		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> end;
		void setStart();
		void setEnd();
		Execution() :
			delta(0)
		{}
	}Execution;

	typedef struct Timer
	{
		Execution cycle;
		Execution frame;
		Execution input;
		Execution script;
		Execution compute;
		Execution output;
		Execution FPS;
		double simulation;
		int lag;
		Timer() :
			simulation(0.0),
			lag(0) 
		{}
	}Timing;
}