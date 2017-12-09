/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Keyboard
*
* Defines the procedures for detecting key presses.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

enum keyStates
{
	NEUTRAL,
	DOWN,
	HELD,
	UP,
};

namespace Input
{
	bool isPressed(
		unsigned char input,
		unsigned char keyBuffer[]);

	bool isReleased(
		unsigned char input,
		unsigned char keyBuffer[]);

	bool isNeutral(
		unsigned char input,
		unsigned char keyBuffer[]);

	bool isHeldFor(
		unsigned char input,
		double seconds,
		unsigned char keyBuffer[],
		double simulationTime);

	void update(unsigned char keyBuffer[]);
}
