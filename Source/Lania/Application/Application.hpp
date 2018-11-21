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
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
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

		Application()
		{}
	}Application;
}