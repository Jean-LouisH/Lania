/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Logging
*
* Prints to console or log file.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <iostream>
#include <string>

namespace Log
{
	void messageConsole(std::string message);
	void messageFile(std::string message);
};