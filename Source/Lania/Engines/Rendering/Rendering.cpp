#include "Rendering.hpp"
#include <GL/glew.h>

void Lania::Rendering::render(Renderables* renderables, uint8_t renderer, SDL_Window* window)
{
	if (renderer == LANIA_OPENGL_3_3_RENDERER)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}
	else if (renderer == LANIA_VULKAN_1_1_RENDERER)
	{
		;
	}
}