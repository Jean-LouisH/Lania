#include <Application/Scenes/Scene.hpp>
#include <SDL_image.h>

Lania::Texture Lania::Scene::loadTexture(String filepath, SDL_Renderer* SDLRenderer)
{
	Texture texture;

	if (!this->textures.count(filepath))
	{
		SDL_Surface* surface = IMG_Load(filepath.c_str());
		SDL_Texture* data = SDL_CreateTextureFromSurface(
			SDLRenderer, surface);
		texture.data = data;
		texture.pixels.width = surface->w;
		texture.pixels.height = surface->h;
		this->textures.emplace(filepath, texture);
		SDL_FreeSurface(surface);
	}
	else
	{
		texture = this->textures.at(filepath);
	}

	return texture;
}

Mix_Chunk* Lania::Scene::loadSound(String filepath)
{
	Mix_Chunk* sound;

	if (!this->sounds.count(filepath))
	{
		sound = Mix_LoadWAV(filepath.c_str());
		this->sounds.emplace(filepath, sound);
	}
	else
	{
		sound = this->sounds.at(filepath);
	}

	return sound;
}

void Lania::Scene::deleteTexture(Lania::String filepath)
{
	SDL_DestroyTexture(this->textures.at(filepath).data);
	this->textures.erase(filepath);
}

void Lania::Scene::deleteSound(Lania::String filepath)
{
	Mix_FreeChunk(this->sounds.at(filepath));
	this->sounds.erase(filepath);
}

void Lania::Scene::deleteAllTextures()
{
	if (!this->textures.empty())
	{
		for (const auto &pair : this->textures)
		{
			SDL_DestroyTexture(pair.second.data);
		}
		this->textures.clear();
	}
}

void Lania::Scene::deleteAllSounds()
{
	if (!this->sounds.empty())
	{
		for (const auto &pair : this->sounds)
		{
			Mix_FreeChunk(pair.second);
		}
		this->sounds.clear();
	}
}

void Lania::Scene::deleteAssets()
{
	this->deleteAllTextures();
	this->deleteAllSounds();
}

void Lania::Scene::addEntity2D(LayerID subscene2D)
{
	Entity2D entity2D;
	this->subscenes2D.at(subscene2D).entities.push_back(entity2D);
}

void Lania::Scene::addEntity2D(LayerID subscene2D, double x, double y)
{
	Entity2D entity2D;
	entity2D.transform.position_px.x = x;
	entity2D.transform.position_px.y = y;
	this->subscenes2D.at(subscene2D).entities.push_back(entity2D);
}

void Lania::Scene::addEntity2D(LayerID subscene2D, double x, double y, double xScale, double yScale)
{
	Entity2D entity2D;
	entity2D.transform.position_px.x = x;
	entity2D.transform.position_px.y = y;
	entity2D.transform.scale.x = xScale;
	entity2D.transform.scale.y = yScale;
	this->subscenes2D.at(subscene2D).entities.push_back(entity2D);
}

void Lania::Scene::addAudioSource2D(LayerID subscene2D, EntityID entityID, String filepath)
{
	this->subscenes2D.at(subscene2D).entities.at(entityID).audioSources.push_back(loadSound(filepath));
}

void Lania::Scene::removeEntity2D(LayerID subscene2D, EntityID entityID)
{
	List<Entity2D>* entities = &this->subscenes2D.at(subscene2D).entities;
	entities->erase(entities->begin() + (entityID - 1));
}