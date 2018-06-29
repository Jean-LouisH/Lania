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

#include <Core/DataStructures/List.hpp>
#include <Core/DataStructures/Stack.hpp>
#include <Core/DataStructures/String.hpp>
#include "Scripting/Variables.hpp"
#include "Scripting/Bytecode.hpp"
#include "Scenes/Scene.hpp"

namespace Lania
{
	typedef struct Application
	{
		Scene scene;
		Variables global;
		Stack<Variables> callStack;
		List<Bytecode> scripts;

		void loadScene(std::string filepath);
		void clearScene();
		SDL_Keycode getSDLKeycode(std::string inputCode);
		unsigned int loadScript(std::string filepath);
		Application()
		{}
	}Application;
}
