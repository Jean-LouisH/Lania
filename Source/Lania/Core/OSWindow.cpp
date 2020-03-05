#include "OSWindow.hpp"
#include "SDL_image.h"

void Lania::OSWindow::create(std::string title, unsigned int width, unsigned int height)
{
	if (!(SDL_WasInit(SDL_INIT_EVERYTHING) & SDL_INIT_VIDEO))
		SDL_Init(SDL_INIT_VIDEO);

	this->window = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_OPENGL);

	this->glContext = SDL_GL_CreateContext(this->window);
	SDL_GL_SetSwapInterval(0);
}

void Lania::OSWindow::sleep(int time_ms)
{
	if (time_ms > 0)
		SDL_Delay(time_ms);
}

void Lania::OSWindow::loadIcon(std::string iconFilePath)
{
	SDL_Surface* icon = IMG_Load(iconFilePath.c_str());
	SDL_SetWindowIcon(this->window, icon);
	SDL_FreeSurface(icon);
}

void Lania::OSWindow::swapBuffers()
{
	SDL_GL_SwapWindow(this->window);
}

void Lania::OSWindow::destroy()
{
	SDL_GL_DeleteContext(this->glContext);
	SDL_DestroyWindow(this->window);
}

uint32_t Lania::OSWindow::getID()
{
	return SDL_GetWindowID(this->window);
}