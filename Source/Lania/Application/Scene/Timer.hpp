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

		double delta_ms;
		double startTime_ms;
		double endTime_ms;
		uint8_t request;
		List<double> deltaLaps_ms;

		Timer() :
			delta_ms(0.0),
			startTime_ms(0.0),
			endTime_ms(0.0),
			request(NO_REQUEST)
		{};
	};
}
