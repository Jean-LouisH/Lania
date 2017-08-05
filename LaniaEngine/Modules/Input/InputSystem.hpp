/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Input System
*
* Houses keyboard, mouse and game controller buffers and methods to process inputs.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

namespace Lania
{
	class InputSystem
	{
	private:
	public:
		bool keyboardBuffer[128];
		bool isPressed(unsigned char input);
	};
}
