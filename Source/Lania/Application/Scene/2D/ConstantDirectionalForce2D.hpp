/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Constant Directional Force 2D
*
* A component that applies a constant force and torque.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "Entity2D.hpp"
#include "../../../Utilities/Mathematics/Vector2.hpp"

namespace Lania
{
	typedef struct ConstantDirectionalForce2D
	{
		EntityID entityID;
		Vector2 force_N;

		ConstantDirectionalForce2D():
			entityID(NO_PARENT)
		{}
	}ConstantDirectionalForce2D;
}
