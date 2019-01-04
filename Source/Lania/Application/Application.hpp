/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Application
*
* The layer on top of the engine that accepts developer scripting,
* scene and asset data to define and control the game / simulation.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "../Utilities/DataStructures/List.hpp"
#include "../Utilities/DataStructures/Stack.hpp"
#include "../Utilities/DataStructures/List.hpp"
#include "Scripting/Variables.hpp"
#include "Scripting/Bytecode.hpp"
#include "Scene/Scene.hpp"

namespace Lania
{
	typedef struct Application
	{
		Scene scene;
		Variables global;
		Stack<Variables> callStack;
		List<Bytecode> scripts;

		Application()
		{}
	}Application;
}
