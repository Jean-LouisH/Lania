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

#include "Engine.hpp"
#include <Application/Application.hpp>

namespace Lania
{
	void initialize(Engine* engine);
	void loop(Engine* engine, Application* application);
	void input(Engine* engine);
	void decide(Engine* engine, Application* application);
	void compute(Engine* engine, Application* application);
	void output(Engine* engine);
	void shutdown(Engine* engine, Application* application);
}
