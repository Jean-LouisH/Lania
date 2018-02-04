#include "Keyboard.hpp"

bool Lania::Key::isPressed(
	unsigned char input,
	unsigned char keyBuffer[])
{
	//XOR gated ASCII character for capital or common letters.
	return (keyBuffer[input] == KEY_DOWN || keyBuffer[(input ^ 0x0020)] == KEY_DOWN);
}

bool Lania::Key::isReleased(
	unsigned char input,
	unsigned char keyBuffer[])
{
	return (keyBuffer[input] == KEY_UP || keyBuffer[(input ^ 0x0020)] == KEY_UP);
}

bool Lania::Key::isNeutral(
	unsigned char input,
	unsigned char keyBuffer[])
{
	return (keyBuffer[input] == KEY_NEUTRAL || keyBuffer[(input ^ 0x0020)] == KEY_NEUTRAL);
}

bool Lania::Key::isHeldFor(
	unsigned char input,
	double targetSecondsHeld,
	unsigned char keyBuffer[],
	double simulationTime)
{
	static double startTime = 0.0;
	static bool completed = false;
	bool flag = false;

	if ((keyBuffer[input] == KEY_HELD ||
		keyBuffer[(input ^ 0x0020)] == KEY_HELD) &&
		!completed)
	{
		if ((simulationTime - startTime) > targetSecondsHeld)
		{
			startTime = simulationTime;
			flag = true;
			completed = true;
		}
	}
	else if (keyBuffer[input] == KEY_NEUTRAL)
	{
		startTime = simulationTime;
		completed = false;
	}

	return (flag);
}

void Lania::Key::update(unsigned char keyBuffer[])
{
	for (int i = 0; i < 128; i++)
	{
		if (keyBuffer[i] == KEY_DOWN)
			keyBuffer[i] = KEY_HELD;
		if (keyBuffer[i] == KEY_UP)
			keyBuffer[i] = KEY_NEUTRAL;
	}
}
