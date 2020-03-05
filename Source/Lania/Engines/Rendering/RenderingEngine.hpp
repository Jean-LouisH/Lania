#pragma once

#include <stdint.h>

namespace Lania
{
	class RenderingEngine
	{
	private:
		uint8_t renderer;
	public:
		enum renderers
		{
			NO_RENDERER,
			LANIA_SDL_2_RENDERER,
			LANIA_OPENGL_3_3_RENDERER,
		};

		RenderingEngine();
	};
}