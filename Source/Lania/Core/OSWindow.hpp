#pragma once

#include <SDL.h>
#include <Utilities/GenericCollections/String.hpp>

namespace Lania
{
	class OSWindow
	{
	private:
		SDL_Window* window;
		SDL_GLContext glContext;
		SDL_Surface* icon;
	public:
		void create(std::string title, unsigned int width, unsigned int height);
		void destroy();
		void swapBuffers();
		void sleep(int time_ms);
		void loadIcon(std::string iconFilePath);
		uint32_t getID();
	};
}