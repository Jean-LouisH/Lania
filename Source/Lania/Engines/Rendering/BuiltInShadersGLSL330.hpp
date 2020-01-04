/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Built-In Shaders
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
		namespace OpenGL33
		{
			const char defaultVertexShader[] = R"(

				#version 330 core
				layout (location = 0) in vec4 vertex;

				out vec2 texCoords;

				uniform mat4 model;
				uniform mat4 projection;

				void main()
				{
					texCoords = vertex.zw;
					gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
				}	
			)";

			const char defaultFragmentShader[] = R"(

				#version 330 core
				in vec2 texCoords;
				out vec4 color;

				uniform sampler2D image;
				uniform vec3 spriteColor;

				void main()
				{    
					color = vec4(spriteColor, 1.0) * texture(image, texCoords);
				}  
			)";
		}
	}
}