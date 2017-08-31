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
		queue<char*> fileCache;
	public:
		char* read(string filePath);
		void write(string filePath, char* fileData);
		void append(string filePath, char* fileData);
		void freeMemory();
	};
}
