/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Core
*
* Forms the lowest layer of data that interfaces with the operating
* system according to what the application layer dictates.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <SDL.h>
#include <Core/HAL/EngineTimers.hpp>
#include "BootConfiguration.hpp"
#include <Core/HAL/Input.hpp>
#include <Core/HAL/Output.hpp>
#include <Core/HAL/Platform.hpp>
#include <Utilities/GenericCollections/String.hpp>
#include <stdint.h>

namespace Lania
{
	typedef struct Core
	{
		enum states
		{
			INITIALIZING,
			RUNNING_APPLICATION_WINDOWED,
			RUNNING_APPLICATION_FULLSCREEN,
			RUNNING_APPLICATION_FULLSCREEN_DESKTOP,
			RESTARTING,
			SHUTDOWN,
		};

		enum renderers
		{
			NO_RENDERER,
			LANIA_SDL_2_RENDERER,
			LANIA_OPENGL_3_3_RENDERER,
		};

		SDL_Window* window;
		SDL_Renderer* sdlRenderer;
		SDL_GLContext glContext;
		uint8_t renderer;
		String filepath;
		String executableName;
		Platform platform;
		EngineTimers engineTimers;
		BootConfiguration bootConfig;
		Input input;
		Output output;
		uint64_t frameCount;
		uint16_t FPS;
		uint8_t state;

		Core() :
			window(NULL),
			sdlRenderer(NULL),
			glContext(NULL),
			renderer(NO_RENDERER),
			frameCount(0),
			FPS(0),
			state(INITIALIZING) {}
	}Core;
}
