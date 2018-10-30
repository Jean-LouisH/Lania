/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* GPU
*
* For hardware specific values and procedures on GPUs.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#ifdef _WIN32

#include <windows.h>
// Use discrete GPU by default.

extern "C" 
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif