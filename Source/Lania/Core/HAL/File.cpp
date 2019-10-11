#include "File.hpp"
#include "MemoryPool.hpp"

bool Lania::FileSystem::exists(String filePath)
{
	FILE* readFile = fopen(filePath.c_str(), "rb");
	if (readFile != NULL)
		fclose(readFile);
	return (bool)readFile;
}

Lania::MemoryPoolU8 Lania::FileSystem::read(String filePath)
{
	FILE* readFile = fopen(filePath.c_str(), "rb");
	MemoryPoolU8 memory;

	if (readFile != NULL)
	{
		fseek(readFile, 0, SEEK_END);
		int capacity = ftell(readFile);
		rewind(readFile);
		memory.allocateUninit(capacity);
		if (memory.getData() != NULL)
			fread(memory.getData(), sizeof(uint8_t), memory.getSize(), readFile);
		fclose(readFile);
	}
	return memory;
}

Lania::MemoryPoolU8 Lania::FileSystem::readString(String filePath)
{
	FILE* readFile = fopen(filePath.c_str(), "rb");
	MemoryPoolU8 memory;

	if (readFile != NULL)
	{
		fseek(readFile, 0, SEEK_END);
		int capacity = ftell(readFile);
		rewind(readFile);
		memory.allocateUninit(capacity + 1);
		if (memory.getData() != NULL)
			fread(memory.getData(), sizeof(uint8_t), memory.getSize(), readFile);
		memory.getData()[memory.getSize() - 1] = '\0';
		fclose(readFile);
	}
	return memory;
}

void Lania::FileSystem::write(String filePath, MemoryPoolU8 memory)
{
	FILE* writeFile = fopen(filePath.c_str(), "wb");
	if (writeFile != NULL)
	{
		fwrite(memory.getData(), sizeof(uint8_t), memory.getSize(), writeFile);
		fclose(writeFile);
	}
}

void Lania::FileSystem::writeString(String filePath, MemoryPoolU8 memory)
{
	FILE* writeFile = fopen(filePath.c_str(), "wb");
	if (writeFile != NULL)
	{
		fwrite(memory.getData(), sizeof(uint8_t), memory.getSize() - 1, writeFile);
		fclose(writeFile);
	}
}

void Lania::FileSystem::append(String filePath, MemoryPoolU8 memory)
{
	FILE* appendFile = fopen(filePath.c_str(), "ab");
	if (appendFile != NULL)
	{
		fwrite(memory.getData(), sizeof(uint8_t), memory.getSize() - 1, appendFile);
		fclose(appendFile);
	}
}

void Lania::FileSystem::appendString(String filePath, MemoryPoolU8 memory)
{
	FILE* appendFile = fopen(filePath.c_str(), "a");
	if (appendFile != NULL)
	{
		fwrite(memory.getData(), sizeof(uint8_t), memory.getSize(), appendFile);
		fclose(appendFile);
	}
}

Lania::String Lania::FileSystem::getExecutableName(Lania::String filePath)
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