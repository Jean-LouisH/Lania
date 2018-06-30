#include "Logging.hpp"
#include <fstream>

void Lania::Log::messageConsole(String message)
{
	std::cout << message << std::endl;
}

void Lania::Log::messageFile(String message)
{
	std::ofstream outputFile;
	outputFile.open("LaniaEngine.log", std::ios::app);
	outputFile << message << std::endl;
	outputFile.close();
}
