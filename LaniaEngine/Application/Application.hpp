/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Application
*
*
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <stack>
#include "Scripting\StackFrame.hpp"

namespace Lania
{
	typedef struct Application
	{
		std::stack<StackFrame> callStack;
	}Application;
}