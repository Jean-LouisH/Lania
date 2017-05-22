/*
**                     This file is part of:
**                         LANIA ENGINE
**
** Copyright(c) 2017 Jean-Louis Haywood
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files(the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions :
**
** The above copyright notice and this permission notice shall be included in all
** copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
** SOFTWARE.
*/

#include "EventSystem.hpp"

Messages EventSystem::handleSDLEvents()
{
	messages.isRunning = true;

	while (SDL_PollEvent(&SDLEvents))
	{
		switch (SDLEvents.type)
		{
			/*Close window button*/
		case SDL_QUIT:
			messages.isRunning = false;
			break;

			/*Keyboard inputs*/
		case SDL_KEYDOWN:
			if (SDLEvents.key.keysym.sym == SDLK_ESCAPE)
			{
				messages.isRunning = false;
			}
			else if (SDLEvents.key.keysym.sym < 128) //ASCII values are below 128.
			{
				messages.keyboardBuffer[SDLEvents.key.keysym.sym] = true;
			}
			break;

		case SDL_KEYUP:
			if (SDLEvents.key.keysym.sym < 128)
			{
				messages.keyboardBuffer[SDLEvents.key.keysym.sym] = false;
			}
			break;
		}
	}

	return messages;
}