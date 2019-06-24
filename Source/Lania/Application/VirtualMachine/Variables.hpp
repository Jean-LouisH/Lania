/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Variables
*
* The variables to be stored statically or on the stack.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "../../Utilities/DataStructures/Vector.hpp"
#include <stdint.h>

namespace Lania
{
	typedef struct Variables
	{
		Vector<uint8_t> uint8s;
		Vector<uint16_t> uint16s;
		Vector<uint32_t> uint32s;
		Vector<uint64_t> uint64s;
		Vector<int8_t> int8s;
		Vector<int16_t> int16s;
		Vector<int32_t> int32s;
		Vector<int64_t> int64s;
		Vector<float> float32s;
		Vector<double> float64s;
	}Variables;
}
