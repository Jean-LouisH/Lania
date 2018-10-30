/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Variables
*
* The variables to be stored statically or on the stack.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Core/DataStructures/List.hpp>
#include <stdint.h>

namespace Lania
{
	typedef struct Variables
	{
		List<uint8_t> uint8s;
		List<uint16_t> uint16s;
		List<uint32_t> uint32s;
		List<uint64_t> uint64s;
		List<int8_t> int8s;
		List<int16_t> int16s;
		List<int32_t> int32s;
		List<int64_t> int64s;
		List<float> float32s;
		List<double> float64s;
	}Variables;
}
