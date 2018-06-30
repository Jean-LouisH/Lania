#include "RendererSDL.hpp"
#include "SDLRenderable.hpp"

void Lania::RendererSDL::drawSprites(
	SDL_Renderer* SDLRenderer,
	SDL_Window* window,
	List<Scene2D>* scene2Ds)
{
	int windowWidth_px = 0;
	int windowHeight_px = 0;
	SDL_GetWindowSize(window, &windowWidth_px, &windowHeight_px);

	SDL_SetRenderDrawColor(SDLRenderer, 0, 0, 0, 255);
	SDL_RenderClear(SDLRenderer);

	int scene2DCount = scene2Ds->size();
	for (int i = 0; i < scene2DCount; i++)
	{
		Scene2D* scene2D = &scene2Ds->at(i);

		int spriteCount = scene2D->sprites.size();
		for (int j = 0; j < spriteCount; j++)
		{
			Sprite* sprite = &scene2D->sprites.at(i);
			Camera2D* camera = NULL;

			for (int k = 0; k < scene2D->cameras.size(); k++)
			{
				camera = &scene2D->cameras.at(i);
				if (camera->current)
					break;
			}

			SDL_RendererFlip flip = SDL_FLIP_NONE;

			if (sprite->xFlip)
				flip = SDL_FLIP_HORIZONTAL;
			if (sprite->yFlip)
				flip = SDL_FLIP_VERTICAL;

			double spriteWidth = sprite->pixels.width;
			double spriteHeight = sprite->pixels.height;
			double cameraWidth = camera->viewport_px.width;
			double cameraHeight = camera->viewport_px.height;
			double cameraX = camera->container->transform.position_px.x;
			double cameraY = camera->container->transform.position_px.y;
			double spriteX = sprite->container->transform.position_px.x;
			double spriteY = sprite->container->transform.position_px.y;

			SDLRenderable renderable = {
				sprite->texture,
				{0,0, spriteWidth, spriteHeight },
				{(int)((((spriteX - spriteWidth / 2 - cameraX) / cameraWidth) + 0.5) * (double)windowWidth_px),
				(int)((((cameraY - spriteY - spriteHeight / 2) / cameraHeight) + 0.5) * (double)windowHeight_px),
				(int)(spriteWidth / cameraWidth * (double)windowWidth_px),
				(int)(spriteHeight / cameraHeight * (double)windowHeight_px)}
			};

			SDL_RenderCopyEx(
				SDLRenderer,
				renderable.texture,
				&renderable.textureRect,
				&renderable.renderingRect,
				-(sprite->container->transform.rotation_rad * M_PI) * (180 / M_PI),
				NULL,
				flip);
		}
	}

	SDL_RenderPresent(SDLRenderer);
}