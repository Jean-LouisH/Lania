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

#include "SDL.h"
#include "GL/glew.h"
#include <vector>

#include "LaniaEngine.hpp"
#include "EngineData.hpp"
#include "Timing.hpp"
#include "UnitTesting.hpp"
#include "OS/File.hpp"
#include "OS/Logging.hpp"
#include "OS/OS.hpp"
#include "../Input/Keyboard.hpp"
#include "../Scenes/2D/Camera2D.hpp"
#include "../Scenes/2D/Sprite.hpp"

int main(int argc, char* argv[])
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
	//std::vector<std::string> image_layers;
	std::string background_layer;
	std::vector<std::string> input_event_map;
	std::vector<Camera_2D> cameras;

	while(engine.state != Lania::gameStates::SHUTDOWN)
	{
		OS::handleEvents(&engine);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SDL_GL_SwapWindow(engine.window);
		timing.current = SDL_GetTicks();
		timing.simulation += (timing.current - timing.last);
		timing.last = timing.current;
		SDL_Delay(1000 / engine.targetFPS);
		Input::update(engine.keyBuffer);
	}

	Lania::shutdown(&engine);
	return 0;
}
