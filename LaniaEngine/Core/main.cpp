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
#include "Engine.hpp"
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
	const int MS_PER_UPDATE = 8;

	Lania::Timing time;
	Lania::Engine engine = Lania::init();

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
		time.cycleStart = SDL_GetTicks();
		OS::handleEvents(&engine);

		time.simulation += time.frame;
		time.lag += time.frame;

		while (time.lag >= MS_PER_UPDATE)
		{
			time.lag -= MS_PER_UPDATE;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SDL_GL_SwapWindow(engine.window);
		Input::update(engine.keyBuffer);

		time.cycleEnd = SDL_GetTicks();
		time.cycleDelta = time.cycleEnd - time.cycleStart;
		time.frameDelay = (1000.0 / engine.targetFPS) - time.cycleDelta;
		if (time.frameDelay > 0 && engine.targetFPS != -1)
			SDL_Delay(time.frameDelay);
		time.frame = SDL_GetTicks() - time.cycleStart;
	}
	Lania::shutdown(&engine);
	return 0;
}
