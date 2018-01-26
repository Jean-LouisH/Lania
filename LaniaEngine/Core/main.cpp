/**
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Lania Engine, named after the Laniakea Supercluster
* (Hawaiian for "immeasurable heaven"), is a 2D/3D
* real-time simulation and game engine.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#include "SDL.h"
#include "LaniaEngine.hpp"

int main(int argc, char* argv[])
{
	Lania::Engine engine;
	Lania::Application application;
	
	Lania::initialize(&engine);
	Lania::loop(&engine, &application);
	Lania::shutdown(&engine, &application);
	return 0;
}
