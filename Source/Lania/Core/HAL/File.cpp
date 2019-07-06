#include "File.hpp"
#include <fstream>

bool Lania::File::exists(String filePath)
{
	std::ifstream file;

	file.open(filePath);
	if (file)
		file.close();
	return (bool)file;
}

char* Lania::File::read(String filePath)
{
	std::ifstream inputFile;

	inputFile.open(filePath, std::ios::binary);
	inputFile.seekg(0, std::ios::end);
	int size = inputFile.tellg();
	char* buffer = new char[size];
	inputFile.seekg(0, std::ios::beg);
	inputFile.read(buffer, size);
	inputFile.close();
	return buffer;
}

void Lania::File::write(String filePath, char* fileData)
{
	std::ofstream outputFile;

	outputFile.open(filePath, std::ios::binary);
	//outputFile.write(fileData, size);
	outputFile.close();
}

void Lania::File::append(String filePath, char* fileData)
{
	std::ofstream outputFile;

	outputFile.open(filePath, std::ios::binary, std::ios::app);
	//outputFile.write(fileData, size);
	outputFile.close();
}

Lania::String Lania::File::getExecutableName(Lania::String filePath)
{
	String executableName;
	int nameIndexStart = 0;

	//Find the first slash from the end
	for (nameIndexStart = filePath.size() - 1; 
		filePath.at(nameIndexStart) != '/' && filePath.at(nameIndexStart) != '\\';
		nameIndexStart--)
		;

	//append from the start index to the extension name.
	for (int j = nameIndexStart + 1; filePath.at(j) != '.'; j++)
		executableName += filePath.at(j);

	return executableName;
}