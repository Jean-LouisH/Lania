/**
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Lania Engine, named after the Laniakea Supercluster
* (Hawaiian for "immeasurable heaven"), is a 2D/3D
* real-time simulation and game engine.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* Created: 5th March 2017
*/

#pragma once

#include <SDL.h>
#include "CommandLine.hpp"
#include "EngineConfiguration.hpp"
#include "FileSystem.hpp"
#include "Mathematics.hpp"
#include "Networker.hpp"
#include "Performance.hpp"
#include "RuntimeData.hpp"
#include "Timer.hpp"
#include "UI.hpp"
#include "../AIEngine/AIEngine.hpp"
#include "../AudioEngine/AudioEngine.hpp"
#include "../Events/EventSystem.hpp"
#include "../Input/InputSystem.hpp"
#include "../Interpreter/Interpreter.hpp"
#include "../PhysicsEngine/PhysicsEngine.hpp"
#include "../RenderingEngine/RenderingEngine.hpp"

class LaniaEngine
{
private:
	/*Lania Data*/
	Lania::Messages messages;
	Lania::RuntimeData runtime;

	/*3rd Party SDK Data*/
	SDL_GLContext context;
	SDL_Window *window;

	/*Lania Core Utilities*/
	Lania::CommandLine commandLine;
	Lania::EngineConfiguration engineConfig;
	Lania::FileSystem fileSystem;
	Lania::Networker networker;
	Lania::Performance performance;
	Lania::Timer timer;
	Lania::UI ui;


	/*Lania Engine Modules*/
	Lania::AIEngine aiEngine;
	Lania::AudioEngine audioEngine;
	Lania::EventSystem eventSystem;
	Lania::InputSystem inputSystem;
	Lania::Interpreter interpreter;
	Lania::PhysicsEngine physicsEngine;
	Lania::RenderingEngine renderingEngine;

	void dispatchMessages(Lania::Messages messages);
public:
	void initialize();
	void runSimulationLoop();
	void shutdown();
};
