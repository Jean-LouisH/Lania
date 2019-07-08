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
#include "../../Core/Core.hpp"

#ifdef _WIN32
#include <windows.h>

typedef void(__stdcall* cpp_init)(Lania::Scene*, Lania::Core* core);
typedef void(__stdcall* cpp_interpretStartLogic)(Lania::Scene*, Lania::Core* core);
typedef void(__stdcall* cpp_interpretInputLogic)(Lania::Scene*, Lania::Core* core);
typedef void(__stdcall* cpp_interpretProcessLogic)(Lania::Scene*, Lania::Core* core);
typedef void(__stdcall* cpp_interpretComputeLogic)(Lania::Scene*, Lania::Core* core, unsigned int computeTimeDelta_ms);
typedef void(__stdcall* cpp_interpretLateLogic)(Lania::Scene*, Lania::Core* core);
typedef void(__stdcall* cpp_interpretFinalLogic)(Lania::Scene*, Lania::Core* core);
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
		void init(Scene* scene, Core* core);
		void interpretStartLogic(Scene* scene, Core* core);
		void interpretInputLogic(Scene* scene, Core* core);
		void interpretFrameLogic(Scene* scene, Core* core);
		void interpretComputeLogic(Scene* scene, Core* core, unsigned int computeTimeDelta_ms);
		void interpretLateLogic(Scene* scene, Core* core);
		void interpretFinalLogic(Scene* scene, Core* core);
	};
}
