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
#include <Core/HAL/GPU.hpp>
#include <Core/HAL/Logging.hpp>
#include <Lania.hpp>

int main(int argc, char* argv[])
{	
	bool restarting = false;

	do
	{
		Lania::Core* core = new Lania::Core();
		Lania::Application* application = new Lania::Application(core);

		core->filepath = argv[0];

		Lania::Log::toConsole("\t\tLania Debug Console\n");

		Lania::initialize(core);
		if (core->state != Lania::Core::states::SHUTDOWN)
			Lania::loop(core, application);
		Lania::shutdown(core);

		restarting = (core->state == Lania::Core::states::RESTARTING);

		delete application;
		delete core;

		Lania::Log::toConsole("Shutdown...");
	} while (restarting);

	return 0;
}
