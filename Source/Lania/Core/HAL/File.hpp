/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* File
*
* Handles all file input and output requests throughout the engine.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "../../Utilities/GenericCollections/String.hpp"
#include "MemoryPool.hpp"
#include <stdint.h>

namespace Lania
{
	namespace File
	{
		bool exists(String filePath);
		MemoryPoolU8 read(String filePath);
		MemoryPoolU8 readString(String filePath);
		void write(String filePath, MemoryPoolU8 memory);
		void writeString(String filePath, MemoryPoolU8 memory);
		void append(String filePath, MemoryPoolU8 memory);
		void appendString(String filePath, MemoryPoolU8 memory);
		String getExecutableName(String filePath);
	}
}

