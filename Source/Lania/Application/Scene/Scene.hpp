/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Scene
*
* Creates, manages and deletes data structures that define active scenes.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Utilities/DataStructures/Map.hpp>
#include <Core/HAL/Input.hpp>
#include <Utilities/Definitions/Aliases.hpp>
#include <Utilities/DataStructures/List.hpp>
#include <Utilities/DataStructures/String.hpp>
#include <stdint.h>
#include "2D/Scene2D.hpp"

namespace Lania
{
	enum LayerTypes
	{
		SUBSCENE_2D,
		SUBSCENE_3D
	};

	class Scene
	{
	private:
	public:
		List<Scene2D> subScenes2D;
		List<LayerType> layers;
		Multimap<String, SDL_Keycode> actionInputMaps;
		Map<String, Texture> textures;
		Rectangle windowDimensions;
		String dataFilePath;

		void load(String filePath);
		Texture loadTexture(String filePath);

		/*Scene modifier methods*/
		void addAudioSource2D(LayerID scene2DID, EntityID entityID, String filepath);
		void addBoxCollider2D(LayerID scene2DID, EntityID entityID, double xMin, double yMin, double xMax, double yMax);
		void addEntity2D(LayerID scene2DID);
		void addEntity2D(LayerID scene2DID, double x, double y);
		void addEntity2D(LayerID scene2DID, String name, double x, double y, double rotation, double xScale, double yScale);
		void addCamera2D(LayerID scene2DID, EntityID entityID);
		void addPointLock2D(LayerID scene2DID, EntityID entityID, double x, double y);
		void addRigidBody2D(LayerID scene2DID, EntityID entityID);
		void addScene2D();
		void addSprite2D(LayerID scene2DID, EntityID entityID);
		void addSpriteTextureFrame(LayerID scene2DID, ComponentListIndex componentIndex, String filepath);
		void centreEntity2DToSprite(LayerID scene2DID, EntityID entityID, ComponentListIndex componentIndex);
		void centreCurrentCamera2DToSprite(LayerID scene2DID, ComponentListIndex componentIndex);
		void deleteAllSounds();
		void deleteAllTextures();
		void deleteAssets();
		void deleteSound(String filepath);
		void deleteTexture(String filepath);
		void flipSprite2D(LayerID scene2DID, ComponentListIndex componentIndex, bool flip);
		void removeEntity2D(LayerID scene2DID, EntityID entityID);
		void setCamera2DInactive(LayerID scene2DID, ComponentListIndex componentIndex);
		void setRigidBody2DInactive(LayerID scene2DID, ComponentListIndex componentIndex);
		void setSprite2DInactive(LayerID scene2DID, ComponentListIndex componentIndex);
	};
}
