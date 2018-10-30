#include "Logging.hpp"
#include <fstream>

void Lania::Log::messageConsole(String message)
{
#if _DEBUG
	std::cout << message << std::endl;
#endif
}

void Lania::Log::messageFile(String message)
{
#if _DEBUG
	std::ofstream outputFile;
	outputFile.open("Lania.log", std::ios::app);
	outputFile << message << std::endl;
	outputFile.close();
#endif
}
