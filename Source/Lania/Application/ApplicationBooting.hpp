/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Application Booting
*
* Populates application configuration
*
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Core/BootConfiguration.hpp>
#include <Utilities/GenericCollections/String.hpp>

namespace Lania
{
	namespace ApplicationBooting
	{
		void build(BootConfiguration* bootConfig);
	}
}
