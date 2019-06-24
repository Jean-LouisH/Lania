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

#include "../Scene/Scene.hpp"

#ifdef _WIN32
	#include <windows.h>

	typedef void(__stdcall* cpp_init)(Lania::Scene*);
	typedef void(__stdcall* cpp_interpretStartLogic)(Lania::Scene*);
	typedef void(__stdcall* cpp_interpretInputLogic)(Lania::Scene*);
	typedef void(__stdcall* cpp_interpretProcessLogic)(Lania::Scene*);
	typedef void(__stdcall* cpp_interpretComputeLogic)(Lania::Scene*, unsigned int);
	typedef void(__stdcall* cpp_interpretLateLogic)(Lania::Scene*);
	typedef void(__stdcall* cpp_interpretFinalLogic)(Lania::Scene*);
#endif

namespace Lania
{
	class Native
	{
	private:
#ifdef _WIN32
		cpp_init native_init;
		cpp_interpretStartLogic native_interpretStartLogic;
		cpp_interpretInputLogic native_interpretInputLogic;
		cpp_interpretProcessLogic native_interpretProcessLogic;
		cpp_interpretComputeLogic native_interpretComputeLogic;
		cpp_interpretLateLogic native_interpretLateLogic;
		cpp_interpretFinalLogic native_interpretFinalLogic;
		void linkWindowsDLL();
#endif
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
