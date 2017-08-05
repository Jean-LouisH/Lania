/**
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Lania Engine, named after the Laniakea Supercluster
* (Hawaiian for "immeasurable heaven"), is a data oriented 2D/3D
* real-time simulation and game engine.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
* Created: 5th March 2017
*/

#pragma once

#include <SDL.h>
#include "EngineConfiguration.hpp"
#include "FileSystem.hpp"
#include "Mathematics.hpp"
#include "Performance.hpp"
#include "RuntimeData.hpp"
#include "Timer.hpp"
#include "../Modules/AIEngine/AIEngine.hpp"
#include "../Modules/AudioEngine/AudioEngine.hpp"
#include "../Modules/Console/Console.hpp"
#include "../Modules/Events/EventSystem.hpp"
#include "../Modules/Input/InputSystem.hpp"
#include "../Modules/Interpreter/Interpreter.hpp"
#include "../Modules/Networker/Networker.hpp"
#include "../Modules/PhysicsEngine/PhysicsEngine.hpp"
#include "../Modules/RenderingEngine/RenderingEngine.hpp"
#include "../Modules/UI/UI.hpp"

class LaniaEngine
{
private:
	/*Lania Data*/
	Lania::Messages messages;
	Lania::RuntimeData runtime;

	/*3rd Party SDK Data*/
	SDL_GLContext context;
	SDL_Window *window;

	/*Lania Kernel Utilities*/
	Lania::EngineConfiguration engineConfig;
	Lania::FileSystem fileSystem;
	Lania::Performance performance;
	Lania::Timer timer;

	/*Lania Engine Modules*/
	Lania::AIEngine aiEngine;
	Lania::AudioEngine audioEngine;
	Lania::Console console;
	Lania::EventSystem eventSystem;
	Lania::InputSystem inputSystem;
	Lania::Interpreter interpreter;
	Lania::Networker networker;
	Lania::PhysicsEngine physicsEngine;
	Lania::RenderingEngine renderingEngine;
	Lania::UI ui;
public:
	void initialize();
	void runSimulationLoop();
	void shutdown();
};
