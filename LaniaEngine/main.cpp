/**
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Lania, named after the Laniakea Supercluster
* (Hawaiian for "immeasurable heaven"), is a 2D/3D
* real-time simulation and game engine.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#include "SDL.h"
#include <Rendering/GPU.hpp>
#include <Core/OS/Logging.hpp>
#include "Core/Lania.hpp"

int main(int argc, char* argv[])
{	
	bool restarting = false;

	do
	{
		Lania::Core* core = new Lania::Core();
		Lania::Application* application = new Lania::Application();

		core->filepath = argv[0];

		Lania::Log::messageConsole("\t\tLania Debug Console");

		Lania::initialize(core);
		if (core->state != Lania::SHUTDOWN)
			Lania::loop(core, application);
		Lania::shutdown(core, application);

		restarting = (core->state == Lania::RESTARTING);

		delete application;
		delete core;
	} while (restarting);

	return 0;
}
