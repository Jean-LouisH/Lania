/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Asset Cache
*
* Contains all assets within the scene to prevent replication of memory allocation
* when loading assets more than once.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <Core/DataStructures/Map.hpp>
#include <Core/DataStructures/String.hpp>
#include <Application/Scenes/Texture.hpp>
#include <SDL_mixer.h>

namespace Lania
{
	typedef struct AssetCache
	{
		Map<String, Texture> textures;
		Map<String, Mix_Chunk*> sounds;
	}AssetCache;
}