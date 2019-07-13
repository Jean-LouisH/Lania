/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Constant Point Force 2D
*
* A component that applies a constant scalar attraction or repulsion force from a point.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "Entity2D.hpp"

namespace Lania
{
	typedef struct ConstantPointForce2D
	{
		EntityID entityID;
		double force_N;

		ConstantPointForce2D() :
			entityID(NO_ENTITY)
		{}
	}ConstantPointForce2D;
}
