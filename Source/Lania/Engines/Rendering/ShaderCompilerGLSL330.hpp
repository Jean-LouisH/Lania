/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Shader Compiler GLSL 330
*
* Code for handling GLSL compilation and verification.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <GL/glew.h>
#include <Utilities/GenericCollections/List.hpp>
#include <Utilities/GenericCollections/String.hpp>

namespace Lania
{
	namespace Rendering
	{
		namespace OpenGL33
		{
			class ShaderCompilerGLSL330
			{
			private:
				List<GLuint> vertexShaders;
				List<GLuint> fragmentShaders;
				GLuint shaderProgram;
				bool compileVertexShader(String vertexShaderSource);
				bool compileFragmentShader(String fragmentShaderSource);
				void linkShaderProgram();
				bool checkCompileTimeErrors(GLuint ID, GLuint status);
				void deleteShaders();
			public:
				void compileShaders(List<String>* vertexShaderSources, List<String>* fragmentShaderSources);
				void use();
				void setIntUniform(String name, int value);
			};
		}
	}
}