#include "Timer.hpp"

void Lania::ExecutionTimer::setStart()
{
	this->start = std::chrono::high_resolution_clock::now();
}

void Lania::ExecutionTimer::setEnd()
{
	this->end = std::chrono::high_resolution_clock::now();
	this->delta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}
