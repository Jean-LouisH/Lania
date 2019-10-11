/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Constants
*
* Defines constants throughout the engine.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

namespace Lania
{
#define MS_PER_COMPUTE_UPDATE 8

#define TERA 1000000000000.0
#define GIGA 1000000000.0
#define MEGA 1000000.0
#define KILO 1000.0
#define MILLI 0.001
#define MICRO 0.000001
#define NANO 0.000000001
#define PICO 0.000000000001

#define NS_IN_S (1.0 / NANO)
#define NS_IN_MS (MILLI / NANO)
#define MS_IN_S (1.0 / MILLI)
#define S_PER_COMPUTE_UPDATE ((double)MS_PER_COMPUTE_UPDATE / (double)MS_IN_S)
#define COMPUTE_UPDATES_PER_S (1.0 / (double)S_PER_COMPUTE_UPDATE)

#define EARTH_GRAVITY 9.80665
#define GRAVITATIONAL_CONSTANT 6.67408e-11
#define EARTH_MASS 5.9722e24

#define NO_ENTITY 0 

#define DEFAULT_DEBUG_EXPORT_PATH "../../Demos/Exports/Lania/"
#define EDITOR_APPLICATION_NAME "Lania Editor"

	enum LayerTypes
	{
		SUBSCENE_2D,
		SUBSCENE_3D
	};
}
