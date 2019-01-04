/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* ConfigurationParser
*
* Parses configuration files.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "ApplicationConfiguration.hpp"

namespace Lania
{
	namespace Config
	{
		AppConfig parseAppConfig(char* fileContent);
	}
}
