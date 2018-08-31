/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Audio SDL
*
* Handles SDL mixer structs to play songs in sequence or simultaneously.
*
* Copyright (c) 2017 - 2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <SDL_mixer.h>
#include <Core/DataStructures/Queue.hpp>

namespace Lania
{
	namespace Audio
	{
		namespace SDL
		{
			void playSounds(
				Queue<Mix_Chunk*>* immediateSounds,
				Queue<Mix_Chunk*>* scheduledSounds);
		}
	}
}