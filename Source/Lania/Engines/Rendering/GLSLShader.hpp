/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* GLSL Shader
*
* Code for handling GLSL compilation and verification.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <GL/glew.h>
#include <Utilities/DataStructures/List.hpp>
#include <Utilities/DataStructures/String.hpp>

namespace Lania
{
	namespace Rendering
	{
		namespace OpenGL
		{
			class GLSLShaders
			{
			private:
				List<GLuint> vertexShaders;
				List<GLuint> fragmentShaders;
				GLuint shaderProgram;
				bool compileVertexShaders();
				bool compileFragmentShaders();
				void linkShaderProgram();
				bool checkCompileTimeErrors(GLuint ID, GLuint status);
				void deleteShaders();
			public:
				void compileShaders();
				void use();
			};
		}
	}
}