/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Engine
*
* Main Engine class 
*
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Application/Application.hpp>
#include <Engines/Physics/PhysicsEngine.hpp>
#include <Engines/Rendering/RenderingEngine.hpp>
#include <Engines/Audio/AudioEngine.hpp>
#include "OS.hpp"
#include "Profiler.hpp"
#include "ThreadPool.hpp"

namespace Lania
{
	class Engine
	{
	private:
		Application* application;

		AudioEngine* audioEngine;
		PhysicsEngine* physicsEngine;
		RenderingEngine* renderingEngine;

		OSWindow* window;
		Platform* platform;
		Profiler* profiler;
		ThreadPool* threadPool;
		BootConfiguration* bootConfig;

		String filepath;
		String executableName;
		uint64_t frameCount;
		uint16_t FPS;
		uint8_t state;

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