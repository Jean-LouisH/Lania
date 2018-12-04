#include "Timer.hpp"

uint64_t Lania::ExecutionTimer::getDelta_ns()
{
	return this->delta_ns;
}

void Lania::ExecutionTimer::setStart()
{
	this->start = std::chrono::high_resolution_clock::now();
}

void Lania::ExecutionTimer::setEnd()
{
	this->end = std::chrono::high_resolution_clock::now();
	this->delta_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}
