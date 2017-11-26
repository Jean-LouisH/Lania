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
#include <vector>

#include "LaniaEngine.hpp"
#include "EngineData.hpp"
#include "File.hpp"
#include "Timing.hpp"
#include "Logging.hpp"
#include "Events.hpp"
#include "UnitTesting.hpp"

#undef main main //reverses SDL's main definition.

typedef struct
{
	double width;
	double height;
	double angle;
	double target;
}Camera_2D;

typedef struct
{
	std::string texture;
}Sprite;

int main()
{
	Lania::Timing timing = {0.0};
	Lania::EngineData engine = Lania::initialize();

	char* mainSceneContents = File::read(
		"../Demos/Basic/" +
		engine.windowTitle +
		"/Scenes/" +
		engine.mainScene);

	unsigned char dimensions;
	std::string background_audio;
	std::vector<std::string> image_layers;
	std::vector<std::string> input_event_map;
	std::vector<Camera_2D> cameras;

	while(engine.state != Lania::gameStates::SHUTDOWN)
	{
		engine.state = OSEvents::handle();
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
