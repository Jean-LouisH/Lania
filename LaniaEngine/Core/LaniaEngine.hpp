/**
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Lania Engine, named after the Laniakea Supercluster
* (Hawaiian for "immeasurable heaven"), is a 2D & 3D
* real-time simulation and game engine.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include "Core.hpp"
#include <Application/Application.hpp>

namespace Lania
{
	void initialize(Core* core);
	void loop(Core* core, Application* application);
	void input(Core* core);
	void logic(Core* core, Application* application);
	void compute(Core* core, Application* application);
	void output(Core* core);
	void shutdown(Core* core, Application* application);
}
