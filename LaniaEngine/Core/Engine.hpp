/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Engine
*
* Forms the lowest layer of data that interfaces with the operating
* system according to what the application layer dictates.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <iostream>
#include "SDL.h"
#include "GL/glew.h"
#include "Timer.hpp"
#include "Configuration.hpp"
#include "Input.hpp"
#include "Output.hpp"

namespace Lania
{
	enum
	{
		RUNNING_APPLICATION,
		SHUTDOWN,
	};

	typedef struct Engine
	{
		SDL_Window* window;
		SDL_GLContext glContext;
		char* renderingAPI;
		char* platform;
		char* filepath;
		Timer timer;
		AppConfig appConfig;
		Input input;
		Output output;
		long long int frameCount;
		int FPS;
		unsigned char state;
		Engine() :
			window(NULL),
			glContext(NULL),
			renderingAPI(NULL),
			platform(NULL),
			frameCount(0),
			FPS(0),
			state(0) {}
	}Engine;
}
