/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Scene 3D 
*
* Contains components and entities that are processed exclusively
* by 3D algorithms.
*
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "../../../Utilities/Definitions/Aliases.hpp"
#include "../../../Utilities/GenericCollections/Vector.hpp"
#include "../../../Utilities/GenericCollections/Map.hpp"
#include "../../../Utilities/GenericCollections/String.hpp"

#include "Entity3D.hpp"

namespace Lania
{
	typedef struct Scene3D
	{
		Vector<Entity3D> entities;
		Map<String, EntityID> entityNameRegistry;
		ComponentListIndex currentCameraIndex;

		Scene3D()
		{
			//The universal, empty parent entity used for reference
			//in recursive algorithms on child entities.
			Entity3D scene3DEntity;
			this->entities.push_back(scene3DEntity);
		}
	}Scene3D;
}
