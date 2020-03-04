/**
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Lania, named after the Laniakea Supercluster
* (Hawaiian for "immeasurable heaven"), is a 2D & 3D
* real-time simulation and game engine.
*
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Core/Core.hpp>
#include <Application/Application.hpp>

namespace Lania
{
	class Engine
	{
	private:
		Core* core;
		Application* application;

		void sleep();
		void benchmark();
		void input();
		void logic();
		void compute();
		void output();
		void initialize();
		void loop();
		void shutdown();
	public:
		Engine(int argc, char* argv[]);
		~Engine();
		void run();
	};
}