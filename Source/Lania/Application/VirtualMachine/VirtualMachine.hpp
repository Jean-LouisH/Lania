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
		void init(Scene* scene);
		void interpretStartLogic(Scene* scene);
		void interpretInputLogic(Scene* scene);
		void interpretProcessLogic(Scene* scene);
		void interpretComputeLogic(Scene* scene, unsigned int computeTimeDelta_ms);
		void interpretLateLogic(Scene* scene);
		void interpretFinalLogic(Scene* scene);
	};
}