/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Audio Listener 2D
*
*
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "Entity2D.hpp"

namespace Lania
{
	typedef struct AudioListener2D
	{
		EntityID entityID;

		AudioListener2D() :
			entityID(NO_ENTITY)
		{}
	}AudioListener2D;
}
