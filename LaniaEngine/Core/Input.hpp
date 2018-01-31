/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Input
*
*
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include "../Input/Keyboard.hpp"
#include <vector>

enum
{
	KEY_BUFFER_SIZE = 128,
};

typedef struct Input
{
	unsigned char keyBuffer[KEY_BUFFER_SIZE];
	std::vector<Key::KeyEvent> keyEvents;
}Input;