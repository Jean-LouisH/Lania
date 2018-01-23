/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Configuration
*
* Initializes the engine data according to the configuration file.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include "Engine.hpp"

namespace Config
{
	Lania::Engine parseInit(char* fileContent);
}
