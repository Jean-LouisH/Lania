/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Entity2D
*
* Component reference points in the 2D scene graph.
* Contains transform data for components that attach to it.
* Can be inherited by other entity2Ds.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <stdint.h>
#include <limits.h>
#include <Constants.hpp>
#include <Definitions.hpp>
#include <Application/Scenes/2D/Transform2D.hpp>
#include <Core/DataStructures/Set.hpp>
#include <SDL_mixer.h>

namespace Lania
{
	enum Components
	{
		NO_COMPONENT,
		CAMERA2D,
		RIGIDBODY2D,
		SPRITE,
		STATICBODY2D,
		BOXCOLLIDER2D
	};

	typedef struct Entity2D
	{
		Transform2D transform;
		List<EntityID> children;
		EntityID parent;
		Map<ComponentType, ComponentListIndex> components;
		List<Mix_Chunk*> audioSources;
		List<ComponentListIndex> scripts;

		Entity2D() :
			parent(NO_PARENT)
		{}
	}Entity2D;
}
