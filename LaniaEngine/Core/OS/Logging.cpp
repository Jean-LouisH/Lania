#include "Logging.hpp"
#include <fstream>

void Lania::Log::messageConsole(std::string message)
{
	std::cout << message << std::endl;
}

void Lania::Log::messageFile(std::string message)
{
	std::ofstream outputFile;
	outputFile.open("LaniaEngine.log", std::ios::app);
	outputFile << message << std::endl;
	outputFile.close();
}
