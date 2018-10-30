/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* File
*
* Handles all file input and output requests throughout the engine.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Core/DataStructures/String.hpp>
#include <stdint.h>

namespace Lania
{
	namespace File
	{
		bool exists(String filePath);
		char* read(String filePath);
		void write(String filePath, char* fileData);
		void append(String filePath, char* fileData);
		String getExecutableName(String filePath);
	}
}

