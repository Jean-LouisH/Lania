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
#include <queue>

using namespace std;

namespace Lania
{
	class FileSystem
	{
	private:
		queue<char*> occupiedMemory;
	public:
		char* read(string filePath);
		void write(string filePath, char* fileData);
		void append(string filePath, char* fileData);
		void freeMemory();
	};
}
