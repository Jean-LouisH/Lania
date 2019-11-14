#include "ExecutionTimer.hpp"

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
	
	//The delta is stored so that setEnd() can be called at the end of a loop, and the delta 
	//remains the same after a new setStart(). This gives the option of checking the
	//time lapse from a previous loop iteration.
	this->delta_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}