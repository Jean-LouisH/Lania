#include "engine.hpp"

#undef main

int main(int argc, char* argv[])
{
	Lania::Engine lania(argc, argv);
	lania.run();
	return 0;
}