/**
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Lania Engine, named after the Laniakea Supercluster
* (Hawaiian for "immeasurable heaven"), is a 2D/3D
* real-time simulation and game engine.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#include <SDL.h>
#include <GL/glew.h>

#include "LaniaEngine.hpp"
#include "EngineData.hpp"
#include "Timing.hpp"
#include "Logging.hpp"
#include "Events.hpp"

#undef main main //reverses SDL's main definition.

int main()
{
	Lania::Timing timing = {0.0};
	Lania::EngineData engine = Lania::initialize();

	while(engine.state != Lania::gameStates::SHUTDOWN)
	{
		engine.state = handleEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SDL_GL_SwapWindow(engine.window);
		timing.current = SDL_GetTicks();
		timing.simulation += (timing.current - timing.last);
		timing.last = timing.current;
		SDL_Delay(1000 / engine.targetFPS);
	}

	Lania::shutdown(&engine);
	return 0;
}
