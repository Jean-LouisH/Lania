#include "InputSystem.hpp"

bool Lania::InputSystem::isPressed(unsigned char input)
{
	//XOR gated ASCII character for capital or common letters.
	return (keyboardBuffer[input] || keyboardBuffer[(input ^ 0x0020)]);
}
