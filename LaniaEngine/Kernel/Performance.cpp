#include "Performance.hpp"

void Lania::Performance::calculateFPS(double currentTime, double sampledTime)
{
	FPS = passedFrames / (currentTime - sampledTime);
}
