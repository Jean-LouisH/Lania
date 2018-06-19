/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Variables
*
* The variables to be stored statically or on the stack.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <vector>
#include <stdint.h>

namespace Lania
{
	typedef struct Variables
	{
		std::vector<uint8_t> uint8s;
		std::vector<uint16_t> uint16s;
		std::vector<uint32_t> uint32s;
		std::vector<uint64_t> uint64s;
		std::vector<int8_t> int8s;
		std::vector<int16_t> int16s;
		std::vector<int32_t> int32s;
		std::vector<int64_t> int64s;
		std::vector<float> float32s;
		std::vector<double> float64s;
	}Variables;
}
