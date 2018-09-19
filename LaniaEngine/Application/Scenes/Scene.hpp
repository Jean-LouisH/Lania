/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Scene
*
* Creates, manages and deletes data structures that define active scenes.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <Core/DataStructures/Map.hpp>
#include <stdint.h>
#include <Core/Input.hpp>
#include "2D/Scene2D.hpp"
#include <Definitions.hpp>
#include <SDL_render.h>
#include <Core/DataStructures/List.hpp>
#include <Core/DataStructures/String.hpp>

namespace Lania
{
	enum LayerTypes
	{
		SUBSCENE_2D,
		SUBSCENE_3D
	};

	typedef struct Scene
	{
		List<Scene2D> subscenes2D;
		List<LayerType> layers;
		Multimap<String, SDL_Keycode> actionInputMaps;
		Multimap<SDL_Keycode, int> keyScriptMaps;

		Map<String, Texture> textures;
		Map<String, Mix_Chunk*> sounds;

		Texture loadTexture(String filepath, SDL_Renderer* SDLRenderer);
		Mix_Chunk* loadSound(String filepath);
		void deleteTexture(String filepath);
		void deleteSound(String filepath);
		void deleteAllTextures();
		void deleteAllSounds();
		void deleteAssets();

		void addEntity2D(LayerID subscene2D);
		void addEntity2D(LayerID subscene2D, double x, double y);
		void addEntity2D(LayerID subscene2D, double x, double y, double xScale, double yScale);
		void addAudioSource2D(LayerID subscene2D, EntityID entityID, String filepath);
		void removeEntity2D(LayerID subscene2D, EntityID entityID);
	}Scene;
}
