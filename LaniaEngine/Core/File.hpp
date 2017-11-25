/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* File
*
* Handles all file input and output requests throughout the engine.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <string>

namespace File
{
	char* read(std::string filePath);
	void write(std::string filePath, char* fileData);
	void append(std::string filePath, char* fileData);
}