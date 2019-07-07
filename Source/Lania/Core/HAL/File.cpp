#include "File.hpp"
#include "MemoryPool.hpp"

bool Lania::File::exists(String filePath)
{
	FILE* readFile = fopen(filePath.c_str(), "rb");
	if (readFile != NULL)
		fclose(readFile);
	return (bool)readFile;
}

Lania::MemoryPoolU8 Lania::File::read(String filePath)
{
	FILE* readFile = fopen(filePath.c_str(), "rb");
	MemoryPoolU8 memory;

	if (readFile != NULL)
	{
		fseek(readFile, 0, SEEK_END);
		int capacity = ftell(readFile);
		rewind(readFile);
		memory.allocate(capacity);
		if (memory.data != NULL)
			fread(memory.data, sizeof(uint8_t), memory.size, readFile);
		fclose(readFile);
	}
	return memory;
}

Lania::MemoryPoolU8 Lania::File::readString(String filePath)
{
	FILE* readFile = fopen(filePath.c_str(), "rb");
	MemoryPoolU8 memory;

	if (readFile != NULL)
	{
		fseek(readFile, 0, SEEK_END);
		int capacity = ftell(readFile);
		rewind(readFile);
		memory.allocate(capacity + 1);
		if (memory.data != NULL)
			fread(memory.data, sizeof(uint8_t), memory.size, readFile);
		memory.data[memory.size - 1] = '\0';
		fclose(readFile);
	}
	return memory;
}

void Lania::File::write(String filePath, MemoryPoolU8 memory)
{
	FILE* writeFile = fopen(filePath.c_str(), "wb");
	if (writeFile != NULL)
	{
		fwrite(memory.data, sizeof(uint8_t), memory.size, writeFile);
		fclose(writeFile);
	}
}

void Lania::File::append(String filePath, MemoryPoolU8 memory)
{

	FILE* appendFile = fopen(filePath.c_str(), "ab");
	if (appendFile != NULL)
	{
		fwrite(memory.data, sizeof(uint8_t), memory.size, appendFile);
		fclose(appendFile);
	}
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