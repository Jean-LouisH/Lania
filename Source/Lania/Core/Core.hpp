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
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <SDL.h>
#include <Core/HAL/Timer.hpp>
#include "ConfigurationParser.hpp"
#include <Core/HAL/Input.hpp>
#include <Core/HAL/Output.hpp>
#include <Core/HAL/Platform.hpp>
#include <Utilities/DataStructures/String.hpp>
#include <stdint.h>

namespace Lania
{
	enum coreStates
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
		LANIA_VULKAN_RENDERER
	};

	typedef struct Core
	{
		SDL_Window* window;
		uint8_t renderer;
		String filepath;
		String executableName;
		Platform platform;
		Timer timer;
		AppConfig appConfig;
		Input input;
		Output output;
		uint64_t frameCount;
		uint16_t FPS;
		uint8_t state;

		Core() :
			window(NULL),
			renderer(LANIA_VULKAN_RENDERER),
			frameCount(0),
			FPS(0),
			state(INITIALIZING) {}
	}Core;
}
