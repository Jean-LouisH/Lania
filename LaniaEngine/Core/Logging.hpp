/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Logging
*
* Prints to console or log file.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/


#pragma once

#include <iostream>
#include <string>

namespace Logging
{
	void toConsole(std::string message);
	void toFile(std::string message);
};