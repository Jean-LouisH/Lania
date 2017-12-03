#include "Logging.hpp"
#include <fstream>

void Log::messageConsole(std::string message)
{
	std::cout << message << std::endl;
}

void Log::messageFile(std::string message)
{
	std::ofstream outputFile;
	outputFile.open("LaniaEngine.log", std::ios::app);
	outputFile << message << std::endl;
	outputFile.close();
}