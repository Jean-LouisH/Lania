#include "LaniaEngine.hpp"

using namespace Lania;

void LaniaEngine::initialize()
{
	timer.initialize();
	performance.fpsRefreshDelay = 1.0;
	runtime = engineConfig.parseInitConfig(fileSystem.read("LaniaConfig.cfg"));

	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		SDL_Log("SDL could not initialize because: %s", SDL_GetError());
		runtime.isRunning = false;
	}
	else
	{
		if (runtime.windowXPosition == 0)
		{
			runtime.windowXPosition = SDL_WINDOWPOS_UNDEFINED;
		}

		if (runtime.windowYPosition == 0)
		{
			runtime.windowYPosition = SDL_WINDOWPOS_UNDEFINED;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		window = SDL_CreateWindow(
			runtime.windowTitle.c_str(),
			runtime.windowXPosition,
			runtime.windowYPosition,
			runtime.windowWidthPixels,
			runtime.windowHeightPixels,
			SDL_WINDOW_OPENGL);

		if (window == NULL)
		{
			SDL_Log("SDL could not create the window because: %s", SDL_GetError());
		}

		context = SDL_GL_CreateContext(window);
		SDL_GL_SetSwapInterval(0);
	}
}

void LaniaEngine::runSimulationLoop()
{
	while (runtime.isRunning)
	{
		this->dispatchMessages(eventSystem.handleSDLEvents());

		timer.updateCurrentTime();
		timer.updateEngineTime();

		if (runtime.state != PAUSED)
		{
			timer.updateSimulationTime(runtime.targetFPS);
			//Script, processing and runtime to be added.
		}

		/*Outputs and processing lists.*/
		//console.printFPS(performance.FPS);
		SDL_GL_SwapWindow(window);

		performance.passedFrames++;
		if (timer.calculateElapsedTime() >= performance.fpsRefreshDelay)
		{
			performance.calculateFPS(timer.currentTime, timer.sampledTime);
			performance.passedFrames = 0;
			timer.updateSampledTime();
		}

		fileSystem.freeMemory();
		timer.idle((int)(1000 / runtime.targetFPS));

	}
}

void LaniaEngine::shutdown()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void LaniaEngine::dispatchMessages(Lania::Messages messages)
{
	runtime.isRunning = messages.isRunning;
	*inputSystem.keyboardBuffer = *messages.keyboardBuffer;
}
