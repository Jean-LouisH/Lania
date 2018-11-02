#include "Logging.hpp"
#include <fstream>

void Lania::Log::toConsole(String message)
{
#if _DEBUG
	const int tabWidth = 30;
	int size = message.size();

	for (int i = 0; i < size; i++)
		if (message.at(i) == ':')
			for (int j = 0; (j < (tabWidth - i)) && (i < tabWidth); j++)
				message.insert(i + 1, " ");

	std::cout << message << std::endl;
#endif
}

void Lania::Log::toFile(String message)
{
#if _DEBUG
	std::ofstream outputFile;
	outputFile.open("Lania.log", std::ios::app);
	outputFile << message << std::endl;
	outputFile.close();
#endif
}
