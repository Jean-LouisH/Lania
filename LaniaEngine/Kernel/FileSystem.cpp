#include "FileSystem.hpp"
#include <fstream>

string Lania::FileSystem::read(std::string filePath)
{
	ifstream inputFile;
	string inputContents = "";

	if (filePath.find(".txt") != string::npos ||
		filePath.find(".xml") != string::npos)
	{
		inputFile.open(filePath);
		string loadedContents ((istreambuf_iterator<char>(inputFile)),
			istreambuf_iterator<char>());
		inputContents = loadedContents;
	}
	else
	{
		inputFile.open(filePath, ios::binary);
		inputFile.seekg(0, ios::end);
		streampos size = inputFile.tellg();
		char* memoryBlock = new char [size];
		inputFile.seekg(0, ios::beg);
		inputFile.read(memoryBlock, size);
		inputContents = memoryBlock;
		delete[] memoryBlock;
	}

	inputFile.close();

	return inputContents;
}

void Lania::FileSystem::write(std::string filePath, std::string fileContents)
{
	ofstream outputFile;

	if (filePath.find(".txt") != string::npos ||
		filePath.find(".xml") != string::npos)
	{
		outputFile.open(filePath);
		outputFile << fileContents;
	}
	else
	{
		outputFile.open(filePath, ios::binary);
		outputFile.write(fileContents.c_str(), fileContents.size());
	}

	outputFile.close();
}

void Lania::FileSystem::append(std::string filePath, std::string fileContents)
{
	ofstream outputFile;

	if (filePath.find(".txt") != string::npos ||
		filePath.find(".xml") != string::npos)
	{
		outputFile.open(filePath, ios::app);
		outputFile << fileContents;
	}
	else
	{
		outputFile.open(filePath, ios::binary, ios::app);
		outputFile.write(fileContents.c_str(), fileContents.size());
	}

	outputFile.close();
}
