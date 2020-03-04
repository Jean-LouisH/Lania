/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Rendering2D
*
* Rendering sub engine for 2D graphics.
*
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Core/Renderables.hpp>
#include "ShaderCompilerGLSL330.hpp"
#include <Utilities/GenericCollections/Vector.hpp>
#include <GL/glew.h>

namespace Lania
{
	namespace Rendering2D
	{
		namespace OpenGL33
		{
			void generate2DTextures(
				Sprite2DRenderable* sprites2D,
				int spriteCount,
				Vector<GLuint>* glTextureIDs);
			void delete2DTextures(
				Vector<GLuint>* glTextureIDs);
			void drawSprites(
				Sprite2DRenderable* sprites2D, 
				int spriteCount,
				GLuint* glTextureIDs,
				Camera2DRenderable* currentCamera2D,
				Rendering::OpenGL33::ShaderCompilerGLSL330* glslShaderCompiler);
		}
	}
}