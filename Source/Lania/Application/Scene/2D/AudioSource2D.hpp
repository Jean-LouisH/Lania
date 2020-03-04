/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Audio Source 2D
*
* 
*
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "Entity2D.hpp"

namespace Lania
{
	typedef struct AudioSource2D
	{
		EntityID entityID;

		AudioSource2D() :
			entityID(NO_ENTITY)
		{}
	}AudioSource2D;
}
