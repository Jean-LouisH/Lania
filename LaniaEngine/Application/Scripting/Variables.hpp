/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Variables
*
*
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <vector>

namespace Lania
{
	typedef struct Variables
	{
		std::vector<unsigned char> uint8s;
		std::vector<unsigned short> uint16s;
		std::vector<unsigned int> uint32s;
		std::vector<unsigned long long int> uint64s;
		std::vector<char> int8s;
		std::vector<short> int16s;
		std::vector<int> int32s;
		std::vector<long long int> int64s;
		std::vector<float> floats;
		std::vector<double> doubles;
	}Variables;
}
