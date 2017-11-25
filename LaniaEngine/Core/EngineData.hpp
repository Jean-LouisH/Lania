/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Engine Data
*
* Contains the working data for the engine runtime.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <iostream>
#include <SDL.h>
#include <GL/glew.h>

namespace Lania
{
	enum gameStates
	{
		RUNNING,
		SHUTDOWN,
	};

	typedef struct
	{
		SDL_Window* window;
		SDL_GLContext glContext;
		char* APIVersion;
		char* platform;
		std::string mainScene;
		std::string windowTitle;
		int windowWidthPixels;
		int windowHeightPixels;
		unsigned char windowFlags;
		int targetFPS;
		unsigned char state;
	}EngineData;
}