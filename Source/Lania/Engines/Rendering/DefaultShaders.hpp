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

namespace Lania
{
	namespace Rendering
	{
		const char defaultVertexShader[] =

			"#version 330 core\n"
			"layout(location = 0) in vec3 aPos;\n"
			"void main()"
			"{"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
			"}";

		const char defaultFragmentShader[] =

			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()"
			"{"
			"FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);"
			"}";
	}
}