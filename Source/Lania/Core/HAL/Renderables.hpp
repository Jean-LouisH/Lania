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

#include <Utilities/DataStructures/List.hpp>
#include <Utilities/Mathematics/Transform2D.hpp>
#include <Utilities/Mathematics/Rectangle.hpp>
#include <Application/Scene/Assets/Texture.hpp>
#include <Utilities/DataStructures/String.hpp>
#include <Utilities/Definitions/Aliases.hpp>

namespace Lania
{
	typedef struct Camera2DRenderable
	{
		Transform2D transform_px;
		Rectangle viewport_px;
		List<String> postProcessingShaders;
	}Camera2DRenderable;

	typedef struct Sprite2DRenderable
	{
		Transform2D transform_px;
		Texture texture;
		List<String> shaders2D;
	}Sprite2DRenderable;

	typedef struct Layer2D
	{
		Camera2DRenderable currentCamera2D;
		List<Sprite2DRenderable> sprites2D;
	}Layer2D;

	typedef struct Camera3DRenderable
	{
		List<String> postProcessingShaders;
	}Camera3DRenderable;

	typedef struct MeshRenderable
	{
		List<String> shader3Ds;
	}MeshRenderable;

	typedef struct Layer3D
	{
		Camera3DRenderable currentCamera3D;
		List<MeshRenderable> meshes;
	}Layer3D;

	typedef struct Renderables
	{
		List<Layer2D> layer2Ds;
		List<Layer3D> layer3Ds;
		List<LayerType> layerTypeOrder;
	}Renderables;
}
