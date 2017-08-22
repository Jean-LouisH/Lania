#include "Core/LaniaEngine.hpp"

#undef main main //reverses SDL's main definition.

int main()
{
	LaniaEngine laniaEngine;

	laniaEngine.initialize();
	laniaEngine.runSimulationLoop();
	laniaEngine.shutdown();
	return 0;
}
