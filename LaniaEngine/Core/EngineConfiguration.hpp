/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Engine Configuration
*
* Initializes the engine runtime states according to the configuration file "LaniaConfig.cfg"
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include "RuntimeData.hpp"

namespace Lania
{
	class EngineConfiguration
	{
	private:
	public:
		RuntimeData parseInitConfig(char* fileData);
	};
}
