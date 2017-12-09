#include "Keyboard.hpp"

bool Input::isPressed(
	unsigned char input,
	unsigned char keyBuffer[])
{
	//XOR gated ASCII character for capital or common letters.
	return (keyBuffer[input] == DOWN || keyBuffer[(input ^ 0x0020)] == DOWN);
}

bool Input::isReleased(
	unsigned char input,
	unsigned char keyBuffer[])
{
	return (keyBuffer[input] == UP || keyBuffer[(input ^ 0x0020)] == UP);
}

bool Input::isNeutral(
	unsigned char input,
	unsigned char keyBuffer[])
{
	return (keyBuffer[input] == NEUTRAL || keyBuffer[(input ^ 0x0020)] == NEUTRAL);
}

bool Input::isHeldFor(
	unsigned char input,
	double targetSecondsHeld,
	unsigned char keyBuffer[],
	double simulationTime)
{
	static double startTime = 0.0;
	static bool completed = false;
	bool flag = false;

	if ((keyBuffer[input] == HELD ||
		keyBuffer[(input ^ 0x0020)] == HELD) &&
		!completed)
	{
		if ((simulationTime - startTime) > targetSecondsHeld)
		{
			startTime = simulationTime;
			flag = true;
			completed = true;
		}
	}
	else if (keyBuffer[input] == NEUTRAL)
	{
		startTime = simulationTime;
		completed = false;
	}

	return (flag);
}

void Input::update(unsigned char keyBuffer[])
{
	for (int i = 0; i < 128; i++)
	{
		if (keyBuffer[i] == DOWN)
			keyBuffer[i] = HELD;
		if (keyBuffer[i] == UP)
			keyBuffer[i] = NEUTRAL;
	}
}