/**
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Lania, named after the Laniakea Supercluster
* (Hawaiian for "immeasurable heaven"), is a 2D/3D
* real-time simulation and game engine.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#include <SDL.h>
#include <Core/GPU.hpp>
#include <Core/Logging.hpp>
#include <Lania.hpp>

int main(int argc, char* argv[])
{	
	Lania::Engine lania(argc, argv);
	lania.run();
	return 0;
}
