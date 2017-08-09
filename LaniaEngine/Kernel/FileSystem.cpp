#include "FileSystem.hpp"
#include <fstream>

char* Lania::FileSystem::read(string filePath)
{

	ifstream inputFile;

	/*If it has these extensions, it is interpreted as text
	 *Otherwise it is read as binary data.*/
	if (filePath.find(".txt") != string::npos ||
		filePath.find(".xml") != string::npos ||
		filePath.find(".cfg") != string::npos)
	{
		inputFile.open(filePath);
		string loadedContents((istreambuf_iterator<char>(inputFile)),
			istreambuf_iterator<char>());
		char* fileString = _strdup(loadedContents.c_str());
		inputFile.close();
		this->occupiedMemory.push(fileString);

		return fileString;
	}
	else
	{
		inputFile.open(filePath, ios::binary);
		inputFile.seekg(0, ios::end);
		int size = inputFile.tellg();
		char* buffer = new char[size];

		/*fileData will contain the binary data and its size.*/
		char* fileData = new char[size + sizeof(size)];
		inputFile.seekg(0, ios::beg);
		inputFile.read(buffer, size);

		/*The size of the binary array is stored at the beginning.
		 *It is 4 bytes long with each byte sliced to fit into fileData's arrays.*/
		for (char i = 0; i < sizeof(size); i++)
		{
			fileData[i] = char(size >> 8 * i);
		}

		memcpy(fileData + sizeof(int), buffer, size);
		delete[] buffer;
		inputFile.close();
		this->occupiedMemory.push(fileData);

		return fileData;
	}
}

void Lania::FileSystem::write(string filePath, char* fileData)
{
	ofstream outputFile;

	if (filePath.find(".txt") != string::npos ||
		filePath.find(".xml") != string::npos ||
		filePath.find(".cfg") != string::npos)
	{
		outputFile.open(filePath);
		outputFile << fileData;
	}
	else
	{
		unsigned int size = 0;

		/*The 4 byte size is retrieved from the first 4 cells of fileData.*/
		for (char i = 0; i < sizeof(int); i++)
		{
			unsigned int byteSegment = (unsigned char)fileData[i];
			byteSegment <<= 8 * i;
			size |= byteSegment;
		}

		outputFile.open(filePath, ios::binary);
		outputFile.write(fileData + sizeof(int), size);
	}

	outputFile.close();
}

void Lania::FileSystem::append(string filePath, char* fileData)
{
	ofstream outputFile;

	if (filePath.find(".txt") != string::npos ||
		filePath.find(".xml") != string::npos ||
		filePath.find(".cfg") != string::npos)
	{
		outputFile.open(filePath, ios::app);
		outputFile << fileData;
	}
	else
	{
		unsigned int size = 0;

		/*The 4 byte size is retrieved from the first 4 cells of fileData.*/
		for (char i = 0; i < sizeof(int); i++)
		{
			unsigned int byteSegment = (unsigned char)fileData[i];
			byteSegment <<= 8 * i;
			size |= byteSegment;
		}

		outputFile.open(filePath, ios::binary, ios::app);
		outputFile.write(fileData + sizeof(int), size);
	}

	outputFile.close();
}

void Lania::FileSystem::freeMemory()
{
	while (!this->occupiedMemory.empty())
	{
		char* memorySegment = occupiedMemory.front();
		occupiedMemory.pop();
		delete[] memorySegment;
	}
}
