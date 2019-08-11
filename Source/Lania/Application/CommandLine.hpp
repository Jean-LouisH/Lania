/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Command Line
*
* 
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Core/Core.hpp>
#include "Scene/Scene.hpp"

namespace Lania
{
	class CommandLine
	{
	private:
	public:
		bool isWaitingOnCommand;
		void run(Core* core, Scene* scene);
	};
}
