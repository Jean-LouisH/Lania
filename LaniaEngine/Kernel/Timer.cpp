#include "Timer.hpp"
#include <ctime>
#include <SDL.h>

void Lania::Timer::idle(int delayMilliseconds)
{
	SDL_Delay(delayMilliseconds);
}

void Lania::Timer::initialize()
{
	currentTime = time(NULL);
	startTime = currentTime;
	sampledTime = currentTime;
}

void Lania::Timer::updateCurrentTime()
{
	currentTime = time(NULL);
}

void Lania::Timer::updateEngineTime()
{
	engineTime = currentTime - startTime;
}

void Lania::Timer::updateSimulationTime(int FPS)
{
	simulationTime += 1.0 / FPS;
}

void Lania::Timer::updateSampledTime()
{
	sampledTime = time(NULL);
}

double Lania::Timer::calculateElapsedTime()
{
	return currentTime - sampledTime;
}
