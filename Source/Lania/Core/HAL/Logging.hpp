/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Logging
*
* Prints to console or log file.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <iostream>
#include "../../Utilities/DataStructures/String.hpp"

namespace Lania
{
	namespace Log
	{
		void toConsole(String message);
		void toFile(String message);
	}
}
