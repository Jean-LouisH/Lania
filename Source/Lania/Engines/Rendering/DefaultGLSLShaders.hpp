/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Default Shaders
*
* Shaders that are always rendered by default to give the general look of a Lania application
* even without user defined shaders. User defined shaders can be used together with these shaders, however.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <GL/glew.h>

namespace Lania
{
	namespace Rendering
	{
		namespace OpenGL
		{
			const char defaultVertexShader[] =

				"#version 330 core\n"
				"layout (location = 0) in vec3 aPos;\n"
				"layout (location = 1) in vec3 aColour;\n"
				"layout (location = 2) in vec2 aTexCoord;\n"
				"out vec3 ourColour;\n"
				"out vec2 texCoord;\n"

				"void main()"
				"{"
				"    gl_Position = vec4(aPos, 1.0);"
				"    ourColour = aColour;"
				"    texCoord = aTexCoord;"
				"}";

			const char defaultFragmentShader[] =

				"#version 330 core\n"
				"out vec4 FragColor;\n"
				"in vec3 ourColour;\n"
				"in vec2 texCoord;\n"
				"uniform sampler2D ourTexture;\n"

				"void main()"
				"{"
				"    FragColor = texture(ourTexture, texCoord);"
				"}";
		}
	}
}