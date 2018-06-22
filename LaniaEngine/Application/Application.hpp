/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Application
*
* The layer on top of the engine that accepts developer scripting,
* scene and asset data to define and control the game / simulation.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <vector>
#include <stack>
#include <string>
#include "Scripting/Variables.hpp"
#include "Scripting/Bytecode.hpp"
#include "Scenes/Scenes.hpp"

namespace Lania
{
	typedef struct Application
	{
		Scene scene;
		Variables global;
		std::stack<Variables> callStack;
		std::vector<Bytecode> scripts;

		void loadScene(std::string filepath);
		void clearScene();
		SDL_Keycode getSDLKeycode(std::string inputCode);
		unsigned int loadScript(std::string filepath);
		Application()
		{}
	}Application;
}
