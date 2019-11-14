/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Timer
*
*
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include <Utilities/GenericCollections/List.hpp>

namespace Lania
{
	typedef struct Timer
	{
		enum requestFlags
		{
			NO_REQUEST,
			SET_START,
			SET_END,
			LAP,
			RESET
		};

		double delta_s;
		double startTime_s;
		double endTime_s;
		uint8_t request;
		List<double> deltaLaps_s;

		Timer() :
			delta_s(0.0),
			startTime_s(0.0),
			endTime_s(0.0),
			request(NO_REQUEST)
		{};
	};
}
