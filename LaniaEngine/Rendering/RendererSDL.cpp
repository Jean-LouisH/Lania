#include "RendererSDL.hpp"
#include <limits.h>
#include "SDLRenderable.hpp"

void Lania::RendererSDL::buildRenderablesFromSprites(
	List<SDLRenderable>* SDLRenderables,
	List<Scene2D>* scene2Ds, 
	SDL_Window* window)
{
	SDLRenderables->clear();
	int windowWidth_px = 0;
	int windowHeight_px = 0;
	SDL_GetWindowSize(window, &windowWidth_px, &windowHeight_px);

	int scene2DCount = scene2Ds->size();
	for (int i = 0; i < scene2DCount; i++)
	{
		Scene2D* scene2D = &scene2Ds->at(i);
		Camera2D camera = scene2D->activeCameras.at(scene2D->currentCameraIndex);
		List<Entity2D>* entities = &scene2D->entities;
		Transform2D* cameraTransform = &entities->at(camera.entityID).transform;

		//Gets sprite data pointer to bypass container procedure calls
		//Within this procedure, the sprite container is read-only.
		Sprite2D* sprites = scene2D->activeSprites.data();
		int spriteCount = scene2D->activeSprites.size();
		for (int j = 0; j < spriteCount; j++)
		{
			Sprite2D* sprite = &sprites[j];
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

			renderable.renderingRect.x = (int)((((spriteX - (spriteWidthScaled / 2.0) - cameraX) / cameraWidth) + 0.5) * (double)windowWidth_px);
			renderable.renderingRect.y = (int)((((cameraY - spriteY - (spriteHeightScaled / 2.0)) / cameraHeight) + 0.5) * (double)windowHeight_px);
			renderable.renderingRect.w = (int)(spriteWidthScaled / cameraWidth * (double)windowWidth_px);
			renderable.renderingRect.h = (int)(spriteHeightScaled / cameraHeight * (double)windowHeight_px);

			renderable.rotation = rotationRelativeToCamera;
			renderable.flip = sprite->flip;

			SDLRenderables->push_back(renderable);
		}
	}
}