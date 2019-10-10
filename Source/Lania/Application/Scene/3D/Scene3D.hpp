/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Scene 2D 
*
* Contains components and entities that are processed exclusively
* by 2D algorithms. Is layered with 3D scenes in the Scene struct.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "../../../Utilities/Definitions/Aliases.hpp"
#include "../../../Utilities/GenericCollections/List.hpp"
#include "../../../Utilities/GenericCollections/Map.hpp"
#include "../../../Utilities/GenericCollections/String.hpp"

#include "Entity3D.hpp"

namespace Lania
{
	typedef struct Scene3D
	{
		List<Entity3D> entities;
		Map<String, EntityID> entityNameRegistry;
		ComponentListIndex currentCameraIndex;

		Scene3D()
		{
			//The universal, empty parent entity used for reference
			//in recursive algorithms on child entities.
			Entity3D dummy;
			this->entities.push_back(dummy);
		}
	}Scene3D;
}
