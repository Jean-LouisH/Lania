/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Constants
*
* Defines constants throughout the engine.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#define MS_PER_UPDATE 8

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
#define S_PER_UPDATE ((double)MS_PER_UPDATE / (double)MS_IN_S)
#define UPDATES_PER_S (1.0 / (double)S_PER_UPDATE)

#define EARTH_GRAVITY 9.80665
#define GRAVITATIONAL_CONSTANT 6.67408e-11
#define EARTH_MASS 5.9722e24

#define NO_PARENT 0 