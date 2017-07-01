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

#include "LaniaEngine.hpp"

void LaniaEngine::initialize()
{
	timer.initialize();

	runtime.windowTitle = "Lania Engine";
	runtime.aspectRatio = (16.0 / 9.0);
	runtime.windowHeightPixels = 480;
	runtime.windowWidthPixels = (int)(runtime.windowHeightPixels * 
		runtime.aspectRatio);
	runtime.targetFPS = 60;
	runtime.state = GAMEPLAY;
	runtime.frameCount = 1;
	runtime.isRunning = true;

	performance.passedFrames = 0;
	performance.fpsRefreshDelay = 1.0;

	const char *title = runtime.windowTitle.c_str();
	SDL_Init(SDL_INIT_EVERYTHING);
	sdlWindow = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		runtime.windowWidthPixels,
		runtime.windowHeightPixels,
		SDL_WINDOW_OPENGL);
}

void LaniaEngine::runSimulationLoop()
{
	do
	{
		messages = eventSystem.handleSDLEvents();

		runtime.isRunning = messages.isRunning;
		*inputSystem.keyboardBuffer = *messages.keyboardBuffer;

		timer.updateCurrentTime();
		timer.updateEngineTime();

		if (runtime.state != PAUSED)
		{
			timer.updateSimulationTime(runtime.frameCount,
				runtime.targetFPS);
			//Script, processing and runtime to be added.
			runtime.frameCount++;
			performance.passedFrames++;
		}

		if (timer.calculateElapsedTime() >= performance.fpsRefreshDelay)
		{
			performance.calculateFPS(timer.currentTime, timer.sampledTime);
			performance.passedFrames = 0;
			timer.updateSampledTime();
		}

		/*Outputs and processing lists.*/
		console.printFPS(performance.FPS);
		timer.idle((int)(1000 / runtime.targetFPS));

	} while (runtime.isRunning);
}

void LaniaEngine::shutdown()
{
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}