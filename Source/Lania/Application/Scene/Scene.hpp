/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Scene
*
* Creates, manages and deletes data structures that define active scenes.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Core/DataStructures/Map.hpp>
#include <stdint.h>
#include <Core/Input.hpp>
#include "2D/Scene2D.hpp"
#include <Definitions.hpp>
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
		Rect windowCopy;

		Map<String, Texture> textures;

		Texture loadTexture(String filepath);

		void deleteTexture(String filepath);
		void deleteSound(String filepath);
		void deleteAllTextures();
		void deleteAllSounds();
		void deleteAssets();

		void addScene2D();
		void addEntity2D(LayerID scene2DID);
		void addEntity2D(LayerID scene2DID, double x, double y);
		void addEntity2D(LayerID scene2DID, double x, double y, double xScale, double yScale);
		void addCamera2D(LayerID scene2DID, EntityID entityID);
		void addSprite2D(LayerID scene2DID, EntityID entityID);
		void addBoxCollider2D(LayerID scene2DID, EntityID entityID, double xMin, double yMin, double xMax, double yMax);
		void addRigidBody2D(LayerID scene2DID, EntityID entityID);
		void addPointLock2D(LayerID scene2DID, EntityID entityID, double x, double y);
		void addSpriteTextureFrame(LayerID scene2DID, ComponentListIndex componentIndex, String filepath);
		void removeEntity2D(LayerID scene2DID, EntityID entityID);

		void centreEntity2DToSprite(LayerID scene2DID, EntityID entityID, ComponentListIndex componentIndex);
		void centreCurrentCamera2DToSprite(LayerID scene2DID, ComponentListIndex componentIndex);
		void flipSprite2D(LayerID scene2DID, ComponentListIndex componentIndex, bool flip);

		void setCamera2DInactive(LayerID scene2DID, ComponentListIndex componentIndex);
		void setRigidBody2DInactive(LayerID scene2DID, ComponentListIndex componentIndex);
		void setSprite2DInactive(LayerID scene2DID, ComponentListIndex componentIndex);
		void addAudioSource2D(LayerID scene2DID, EntityID entityID, String filepath);
	}Scene;
}
