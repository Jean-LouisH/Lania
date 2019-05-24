/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Native
*
* Houses native logic code for customized use of Lania's engine code.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Core/Core.hpp>
#include <Application/Application.hpp>

namespace Lania
{
	namespace Native
	{
		void initializeApplication(Core* core, Application* application);
		void processInputs(Core* core, Application* application);
		void updateApplicationLogic(Core* core, Application* application);
	}
}
