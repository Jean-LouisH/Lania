/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* File System
*
* Handles all file input and output requests throughout the engine.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <string>

using namespace std;

namespace Lania
{
	class FileSystem
	{
	private:
	public:
		string read(std::string filePath);
		void write(std::string filePath, std::string fileContents);
		void append(std::string filePath, std::string fileContents);
	};
}
