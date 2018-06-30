/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* OS
*
* Receives inputs and events from the keyboard, mouse and OS messages.
*
* Copyright (c) 2017-2018 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <Core/Engine.hpp>

namespace Lania
{
	namespace OS
	{
		void listenForEvents(Engine* engine);
		void detectGameControllers(Engine* engine);
		void detectBatteryLife(Engine* engine);
		void pollInputEvents(Engine* engine);
		void refreshWindowIcon(Engine* engine);
	}
}
