/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Physics2D
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
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
	}
}