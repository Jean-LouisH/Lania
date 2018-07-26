#include "RendererSDL.hpp"
#include <limits.h>
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
		Camera2D camera = scene2D->activeCameras.at(scene2D->currentCameraIndex);
		List<Entity2D>* entities = &scene2D->entities;
		Transform2D* cameraTransform = &entities->at(camera.entityID).transform;

		//Gets sprite data pointer to bypass container procedure calls
		//Within this procedure, the sprite container is read-only.
		Sprite* sprites = scene2D->activeSprites.data();
		int spriteCount = scene2D->activeSprites.size();
		for (int j = 0; j < spriteCount; j++)
		{
			Sprite* sprite = &sprites[j];
			Transform2D* spriteTransform = &entities->at(sprite->entityID).transform;

			double spriteWidth = sprite->pixels.width;
			double spriteHeight = sprite->pixels.height;
			double spriteWidthScaled = spriteWidth * spriteTransform->scale.x;
			double spriteHeightScaled = spriteHeight * spriteTransform->scale.y;
			double cameraWidth = camera.viewport_px.width;
			double cameraHeight = camera.viewport_px.height;
			double cameraX = cameraTransform->position_px.x;
			double cameraY = cameraTransform->position_px.y;
			double spriteX;
			double spriteY;
			double rotationRelativeToCamera;

			//Offsets sprite by relative position with parent
			EntityID spriteParent = entities->at(sprite->entityID).parent;
			if (spriteParent != ULLONG_MAX)
			{
				Transform2D parentTransform = entities->at(spriteParent).transform;
				spriteX = parentTransform.position_px.x + 
					(spriteTransform->position_px.x * cos(parentTransform.rotation_rad * M_PI) -
					spriteTransform->position_px.y * sin(parentTransform.rotation_rad * M_PI));
				spriteY = parentTransform.position_px.y +
					(spriteTransform->position_px.x * sin(parentTransform.rotation_rad * M_PI) +
					spriteTransform->position_px.y * cos(parentTransform.rotation_rad * M_PI));
				rotationRelativeToCamera =
					-((spriteTransform->rotation_rad + parentTransform.rotation_rad - 
						cameraTransform->rotation_rad) * 180.0);
			}
			else
			{
				spriteX = spriteTransform->position_px.x;
				spriteY = spriteTransform->position_px.y;
				rotationRelativeToCamera =
					-((spriteTransform->rotation_rad - cameraTransform->rotation_rad) * 180.0);
			}

			SDLRenderable renderable;
			renderable.texture = sprite->texture;

			renderable.textureRect.x = 0;
			renderable.textureRect.y = 0;
			renderable.textureRect.w = spriteWidth;
			renderable.textureRect.h = spriteHeight;

			renderable.renderingRect.x = (int)((((spriteX - spriteWidth / 2 - cameraX) / cameraWidth) + 0.5) * (double)windowWidth_px);
			renderable.renderingRect.y = (int)((((cameraY - spriteY - spriteHeight / 2) / cameraHeight) + 0.5) * (double)windowHeight_px);
			renderable.renderingRect.w = (int)(spriteWidthScaled / cameraWidth * (double)windowWidth_px);
			renderable.renderingRect.h = (int)(spriteHeightScaled / cameraHeight * (double)windowHeight_px);

			SDL_RenderCopyEx(
				SDLRenderer,
				renderable.texture,
				&renderable.textureRect,
				&renderable.renderingRect,
				rotationRelativeToCamera,
				NULL,
				sprite->flip);
		}
	}

	SDL_RenderPresent(SDLRenderer);
}