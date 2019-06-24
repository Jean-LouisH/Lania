/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Virtual Machine
*
* Implements the Lania's non-native scripting system.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "../../Utilities/DataStructures/Vector.hpp"
#include "../../Utilities/DataStructures/Stack.hpp"
#include "../Scene/Scene.hpp"
#include "Variables.hpp"
#include "Bytecode.hpp"

namespace Lania
{
	class VirtualMachine
	{
	private:
		Variables global;
		Stack<Variables> callStack;
		Vector<Bytecode> scripts;
	public:
		void initializeLogic(Scene* scene);
		void processInputs(Scene* scene);
		void interpretLogic(Scene* scene);
	};
}