/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Entity2D
*
* Component reference points in the 2D scene graph.
* Contains transform data for components that attach to it.
* Can be inherited by other entity2Ds.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "../../../Utilities/Definitions/Constants.hpp"
#include "../../../Utilities/Definitions/Aliases.hpp"
#include "../../../Utilities/Mathematics/Transform2D.hpp"
#include "../../../Utilities/GenericCollections/Set.hpp"
#include "../../../Utilities/GenericCollections/Vector.hpp"
#include "../../../Utilities/GenericCollections/Map.hpp"
#include "../../../Utilities/GenericCollections/String.hpp"

namespace Lania
{
	typedef struct Entity2D
	{
		enum components
		{
			NO_COMPONENT,
			CAMERA_2D,
			RIGID_BODY_2D,
			SPRITE_2D,
			BOX_COLLIDER_2D,
			POINT_LOCK_2D,
		};

		Transform2D transform;
		Vector<EntityID> children;
		EntityID parent;
		Map<ComponentType, ComponentListIndex> components;
		Set<String> tags;
		Vector<String> shaders2D;
		Vector<ScriptIndex> scripts;

		Entity2D() :
			parent(NO_ENTITY)
		{}
	}Entity2D;
}
