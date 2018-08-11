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
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include "SDL.h"
#include "Timer.hpp"
#include "Configuration.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "Platform.hpp"
#include <stdint.h>

namespace Lania
{
	enum engineStates
	{
		RUNNING_APPLICATION,
		SHUTDOWN,
	};

	enum renderers
	{
		SDL_RENDERER,
		LANIA_OPENGL_RENDERER,
		LANIA_VULKAN_RENDERER,
	};

	typedef struct Engine
	{
		SDL_Window* window;
		SDL_GLContext glContext;
		SDL_Renderer* SDLRenderer;
		uint8_t renderer;
		char* filepath;
		Platform platform;
		Timer timer;
		AppConfig appConfig;
		Input input;
		Output output;
		uint64_t frameCount;
		uint16_t FPS;
		uint8_t state;
		Engine() :
			window(NULL),
			glContext(NULL),
			SDLRenderer(NULL),
			renderer(SDL_RENDERER),
			filepath(NULL),
			frameCount(0),
			FPS(0),
			state(RUNNING_APPLICATION) {}
	}Engine;
}
