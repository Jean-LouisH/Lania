#include "Texture.hpp"

uint8_t* Lania::Texture::getData()
{
	return (uint8_t*) this->surface->pixels;
}

uint64_t Lania::Texture::getSize()
{
	return (this->surface->w * this->surface->h) * (int)this->surface->format->BytesPerPixel;
}

Lania::Rectangle Lania::Texture::getDimensions()
{
	Rectangle dimensions;
	dimensions.width = this->surface->w;
	dimensions.height = this->surface->h;
	return dimensions;
}

double Lania::Texture::getWidth()
{
	return this->surface->w;
}

double Lania::Texture::getHeight()
{
	return this->surface->h;
}

void Lania::Texture::load(String filePath)
{
	this->surface = IMG_Load(filePath.c_str());
}

Lania::Texture::~Texture()
{
	if (this->surface != NULL)
		SDL_FreeSurface(this->surface);
}