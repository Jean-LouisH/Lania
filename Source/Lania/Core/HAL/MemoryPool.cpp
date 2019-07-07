#include "MemoryPool.hpp"
#include <stdlib.h>

Lania::MemoryPoolU8::MemoryPoolU8()
{
	this->deallocate();
}

void Lania::MemoryPoolU8::allocate(uint64_t capacity)
{
	if (capacity > 0)
	{
		this->deallocate();
		this->size = capacity;
		this->data = (uint8_t*)calloc(sizeof(uint8_t), (this->size));
	}
}

void Lania::MemoryPoolU8::allocateUninit(uint64_t capacity)
{
	if (capacity > 0)
	{
		this->deallocate();
		this->size = capacity;
		this->data = (uint8_t*)malloc(sizeof(uint8_t) * (this->size));
	}
}

void Lania::MemoryPoolU8::reallocate(uint64_t newCapacity)
{
	if ((this->data != NULL) && (newCapacity > 0))
		this->data = (uint8_t*) realloc(this->data, newCapacity);
}

void Lania::MemoryPoolU8::deallocate()
{
	if (this->data != NULL)
		free(this->data);
	this->data = NULL;
	this->size = 0;
}