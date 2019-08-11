/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Entity3D
*
* Component reference points in the 3D scene graph.
* Contains transform data for components that attach to it.
* Can be inherited by other entity3Ds.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "../../../Utilities/Definitions/Constants.hpp"
#include "../../../Utilities/Definitions/Aliases.hpp"
#include "../../../Utilities/Mathematics/Transform3D.hpp"
#include "../../../Utilities/DataStructures/Set.hpp"
#include "../../../Utilities/DataStructures/List.hpp"
#include "../../../Utilities/DataStructures/Map.hpp"
#include "../../../Utilities/DataStructures/String.hpp"


namespace Lania
{
	enum Components
	{
		NO_COMPONENT,
		CAMERA_3D,
		RIGID_BODY_3D,
		SPRITE_3D,
		BOX_COLLIDER_3D,
		POINT_LOCK_3D,
	};

	typedef struct Entity3D
	{
		Transform3D transform;
		List<EntityID> children;
		EntityID parent;
		Map<ComponentType, ComponentListIndex> components;
		Set<String> tags;
		List<String> shaders3D;
		List<ScriptIndex> scripts;

		Entity3D() :
			parent(NO_ENTITY)
		{}
	}Entity3D;
}
