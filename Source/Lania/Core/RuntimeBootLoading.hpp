/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Runtime Boot Loading
*
* Populates application configuration
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "BootConfiguration.hpp"
#include <Utilities/GenericCollections/String.hpp>

namespace Lania
{
	namespace RuntimeBootLoading
	{
		void build(BootConfiguration* bootConfig, String filePath);
	}
}
