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

#ifdef _WIN32
	#include <windows.h>
#endif

#include "../Scene/Scene.hpp"

namespace Lania
{
	class Native
	{
	private:
#ifdef _WIN32
		HINSTANCE hGetProcIDDLL;
		void linkWindowsDLL();
#endif
	public:
		void initializeLogic(Scene* scene);
		void processInputs(Scene* scene);
		void interpretLogic(Scene* scene);
	};
}
