#include "Texture.hpp"

uint8_t* Lania::Texture::getData()
{
	return (uint8_t*) this->surface->pixels;
}

uint64_t Lania::Texture::getSize()
{
	return (uint64_t) this->surface->w * (uint64_t) this->surface->h * (uint64_t)this->surface->format->BytesPerPixel;
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

uint8_t Lania::Texture::getBytesPerPixel()
{
	return this->surface->format->BytesPerPixel;
}

void Lania::Texture::load(String filePath)
{
	this->surface = IMG_Load(filePath.c_str());
}

void Lania::Texture::unload()
{
	if (this->surface != NULL)
		SDL_FreeSurface(this->surface);
}

Lania::Texture::~Texture()
{

}