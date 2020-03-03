/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Renderables
*
* Reduced scene data that is only needed by the Rendering Engine.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Utilities/GenericCollections/Vector.hpp>
#include <Utilities/Mathematics/Transform2D.hpp>
#include <Utilities/Mathematics/Rectangle.hpp>
#include <Application/Scene/Assets/Texture.hpp>
#include <Utilities/GenericCollections/String.hpp>
#include <Utilities/Definitions/Aliases.hpp>
#include <Utilities/Mathematics/Colour.hpp>
#include <Application/Scene/Assets/Font.hpp>

namespace Lania
{
	typedef struct Camera2DRenderable
	{
		Transform2D transform_px;
		Rectangle viewport_px;
		Vector<String> postProcessingShaders;
	}Camera2DRenderable;

	typedef struct Sprite2DRenderable
	{
		Transform2D transform_px;
		Texture texture;
		Vector<String> shaders2D;
	}Sprite2DRenderable;

	typedef struct Text2DRenderable
	{
		Transform2D transform_px;
		String text;
		Font font;
		Colour colour;
		Vector<String> shaders2D;
	}Text2DRenderable;

	typedef struct Layer2D
	{
		Camera2DRenderable currentCamera2D;
		Vector<Sprite2DRenderable> sprites2D;
		Vector<Text2DRenderable> texts2D;
	}Layer2D;

	typedef struct Camera3DRenderable
	{
		Vector<String> postProcessingShaders;
	}Camera3DRenderable;

	typedef struct MeshRenderable
	{
		Vector<String> shader3Ds;
	}MeshRenderable;

	typedef struct Layer3D
	{
		Camera3DRenderable currentCamera3D;
		Vector<MeshRenderable> meshes;
	}Layer3D;

	typedef struct Renderables
	{
		Vector<Layer2D> layer2Ds;
		Vector<Layer3D> layer3Ds;
		Vector<LayerType> layerTypeOrder;
		bool hasChanged;

		Renderables()
		{
			this->hasChanged = false;
		}
	}Renderables;
}
