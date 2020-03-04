/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Physics
*
* Delegates physics processing work by components in scene.
*
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Application/Scene/2D/Scene2D.hpp>
#include <Application/Scene/2D/CollisionEvent2D.hpp>
#include <Utilities/GenericCollections/Vector.hpp>

namespace Lania
{
	namespace Physics
	{
		void compute(
			Vector<Scene2D>* subScene2Ds,
			double simulation_ms);
	}
}