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
* Description: Lania Engine, named after the Laniakea Supercluster
* (Hawaiian for "immeasurable heaven"), is a data oriented 2D/3D
* real-time simulation and game engine.
*
* Author: Jean-Louis Haywood
* Created: 5th March 2017
*/

#pragma once

#include <SDL.h>
#include "Performance.hpp"
#include "RuntimeData.hpp"
#include "Timer.hpp"
#include "../Modules/AudioEngine/AudioEngine.hpp"
#include "../Modules/Console/Console.hpp"
#include "../Modules/Events/EventSystem.hpp"
#include "../Modules/Input/InputSystem.hpp"
#include "../Modules/Interpreter/Interpreter.hpp"
#include "../Modules/PhysicsEngine/PhysicsEngine.hpp"
#include "../Modules/RenderingEngine/RenderingEngine.hpp"

class LaniaEngine
{
private:
	RuntimeData runtime;
	SDL_Window *window;
	SDL_GLContext context;
	AudioEngine audioEngine;
	Console console;
	EventSystem eventSystem;
	InputSystem inputSystem;
	Interpreter interpreter;
	PhysicsEngine physicsEngine;
	RenderingEngine renderingEngine;
	Performance performance;
	Timer timer;
	Messages messages;
public:
	void initialize();
	void runSimulationLoop();
	void shutdown();
};