/*
**                     This file is part of:
**                         LANIA ENGINE
**
** Copyright(c) 2017 Jean-Louis Haywood
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files(the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions :
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
*/

#include "Initialization.hpp"

void initializeEngine(RuntimeData* runtimeData, Timer* timer, SDL_Window* SDLWindow)
{
	runtimeData->windowTitle = "Lania Engine";
	runtimeData->aspectRatio = (16.0 / 9.0);
	runtimeData->windowHeightPixels = 480;
	runtimeData->windowWidthPixels = (int)(runtimeData->windowHeightPixels * runtimeData->aspectRatio);
	runtimeData->targetFPS = 60;
	runtimeData->gameState = GAMEPLAY;
	runtimeData->frameCount = 1;
	runtimeData->passedFrames = 0;

	timer->initTime();

	const char* title = runtimeData->windowTitle.c_str();
	SDL_Init(SDL_INIT_EVERYTHING);
	SDLWindow = SDL_CreateWindow(title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		runtimeData->windowWidthPixels,
		runtimeData->windowHeightPixels,
		SDL_WINDOW_OPENGL);
}