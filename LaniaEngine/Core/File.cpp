#include "File.hpp"
#include <fstream>

char* File::read(std::string filePath)
{
	std::ifstream inputFile;

	/*If it has these extensions, it is interpreted as text
	 *Otherwise it is read as binary data.*/
	if (filePath.substr(filePath.find_last_of(".") + 1) == "txt" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "xml" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "cfg" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "log" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "lscn" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "lasc" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "csv")
	{
		inputFile.open(filePath);
		std::string loadedContents((std::istreambuf_iterator<char>(inputFile)),
			std::istreambuf_iterator<char>());
		char* fileString = _strdup(loadedContents.c_str());
		inputFile.close();

		return fileString;
	}
	else
	{
		inputFile.open(filePath, std::ios::binary);
		inputFile.seekg(0, std::ios::end);
		int size = inputFile.tellg();
		char* buffer = new char[size];

		/*fileData will contain the binary data and its size.*/
		char* fileData = new char[size + sizeof(size)];
		inputFile.seekg(0, std::ios::beg);
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

		return fileData;
	}
}

void File::write(std::string filePath, char* fileData)
{
	std::ofstream outputFile;

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

		outputFile.open(filePath, std::ios::binary);
		outputFile.write(fileData + sizeof(int), size);
	}

	outputFile.close();
}

void File::append(std::string filePath, char* fileData)
{
	std::ofstream outputFile;

	if (filePath.substr(filePath.find_last_of(".") + 1) == "txt" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "xml" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "cfg" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "log" ||
		filePath.substr(filePath.find_last_of(".") + 1) == "csv")
	{
		outputFile.open(filePath, std::ios::app);
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

		outputFile.open(filePath, std::ios::binary, std::ios::app);
		outputFile.write(fileData + sizeof(int), size);
	}

	outputFile.close();
}
