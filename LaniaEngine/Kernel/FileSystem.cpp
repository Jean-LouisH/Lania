#include "FileSystem.hpp"
#include <fstream>

char* Lania::FileSystem::read(string filePath)
{

	ifstream inputFile;

	filePath.substr(filePath.find_last_of(".") + 1) == "cfg";

	/*If it has these extensions, it is interpreted as text
	 *Otherwise it is read as binary data.*/
	if (filePath.substr(filePath.find_last_of(".") + 1) == "txt" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "xml" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "cfg" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "log" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "csv")
	{
		inputFile.open(filePath);
		string loadedContents((istreambuf_iterator<char>(inputFile)),
			istreambuf_iterator<char>());
		char* fileString = _strdup(loadedContents.c_str());
		inputFile.close();
		this->fileCache.push(fileString);

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
		this->fileCache.push(fileData);

		return fileData;
	}
}

void Lania::FileSystem::write(string filePath, char* fileData)
{
	ofstream outputFile;

	if (filePath.substr(filePath.find_last_of(".") + 1) == "txt" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "xml" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "cfg" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "log" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "csv")
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

	if (filePath.substr(filePath.find_last_of(".") + 1) == "txt" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "xml" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "cfg" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "log" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "csv")
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
	while (!this->fileCache.empty())
	{
		char* memorySegment = fileCache.front();
		fileCache.pop();
		delete[] memorySegment;
	}
}
