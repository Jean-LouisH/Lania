#include "Timer.hpp"
#include <chrono>

void Lania::Execution::setStart()
{
	this->start = std::chrono::high_resolution_clock::now();
}

void Lania::Execution::setEnd()
{
	this->end = std::chrono::high_resolution_clock::now();
	this->delta = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}