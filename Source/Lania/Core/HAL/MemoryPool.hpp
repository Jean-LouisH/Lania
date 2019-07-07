/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Memory Pool
*
* Block allocation of memory for I/O.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>

namespace Lania
{
	class MemoryPoolU8
	{
	public:
		uint8_t* data;
		uint64_t size;

		MemoryPoolU8();
		void allocate(uint64_t capacity);
		void allocateUninit(uint64_t capacity);
		void reallocate(uint64_t newCapacity);
		void deallocate();
	};
}