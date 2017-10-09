#include "Logging.hpp"
#include <fstream>

void Logging::toConsole(std::string message)
{
	std::cout << message << std::endl;
}

void Logging::toFile(std::string message)
{
	std::ofstream outputFile;
	outputFile.open("LaniaEngine.log", std::ios::app);
	outputFile << message << std::endl;
	outputFile.close();
}