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
#include <Core/DataStructures/String.hpp>

namespace Lania
{
	namespace Log
	{
		void messageConsole(String message);
		void messageFile(String message);
	}
}
