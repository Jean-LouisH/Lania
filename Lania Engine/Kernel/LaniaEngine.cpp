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

/**
* Lania Engine
*
* Description: Lania Engine, named after the Laniakea Supercluster (Hawaiian for
* "immense heaven"), is a 2D and 3D game engine that is being developed for personal
* research, experimentation & fun.
*
* Author:         Jean-Louis Haywood
* Created:        5th March 2017
*/

#include "LaniaEngine.hpp"
#include "Initialization.hpp"
#include "SimulationLoop.hpp"
#include "Shutdown.hpp"
#include "RuntimeData.hpp"
#include "../Modules/Common/Timer/Timer.hpp"
#include <SDL.h>

void run_LaniaEngine()
{
	Timer timer;
	RuntimeData runtimeData;
	static SDL_Window *SDLWindow;

	initializeEngine(&runtimeData, &timer, SDLWindow);
	runSimulationLoop(&runtimeData, &timer, SDLWindow);
	shutdownEngine(SDLWindow);
}