/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Physics2D
*
* Processes rigid body components in bulk to simulate physics.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <Application/Scenes/2D/Scene2D.hpp>

namespace Lania
{
	namespace Physics2D
	{
		void detectCollisions(List<Scene2D>* scene2Ds);
		void gravitate(List<Scene2D>* scene2Ds);
		void displace(List<Scene2D>* scene2Ds);
		void lock(List<Scene2D>* scene2Ds);
	}
}