#include "RenderingSDL.hpp"
#include <limits.h>
#include "SDLRenderable.hpp"
#include <Constants.hpp>

void Lania::Rendering2D::SDL::buildRenderablesFromSprites(
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
		Entity2D* entities = scene2D->entities.data();
		Transform2D* cameraTransform = &entities[camera.entityID].transform;

		//Gets sprite data pointer to bypass container procedure calls
		//Within this procedure, the sprite container is read-only.
		Sprite2D* sprites = scene2D->activeSprites.data();
		int spriteCount = scene2D->activeSprites.size();
		for (int j = 0; j < spriteCount; j++)
		{
			Sprite2D* sprite = &sprites[j];
			Transform2D* spriteTransform = &entities[sprite->entityID].transform;

			double spriteWidth = sprite->textureFrames.at(sprite->frameIndex).pixels.width;
			double spriteHeight = sprite->textureFrames.at(sprite->frameIndex).pixels.height;
			double spriteWidthScaled = spriteWidth * spriteTransform->scale.x;
			double spriteHeightScaled = spriteHeight * spriteTransform->scale.y;
			double cameraWidth = camera.viewport_px.width;
			double cameraHeight = camera.viewport_px.height;
			double cameraX = cameraTransform->position_px.x;
			double cameraY = cameraTransform->position_px.y;
			double spriteX = 0.0;
			double spriteY = 0.0;
			double rotationRelativeToCamera = 0.0;

			//Offsets sprite by relative position with parent
			//along the entity hierachy
			EntityID spriteID = sprite->entityID;
			EntityID spriteParentID;
			do
			{
				spriteParentID = entities[spriteID].parent;
				Transform2D parentTransform = entities[spriteParentID].transform;
				Transform2D currentSpriteTransform = entities[spriteID].transform;

				spriteX += parentTransform.position_px.x +
					(currentSpriteTransform.position_px.x * cos(parentTransform.rotation_rad * M_PI) -
						currentSpriteTransform.position_px.y * sin(parentTransform.rotation_rad * M_PI));
				spriteY += parentTransform.position_px.y +
					(currentSpriteTransform.position_px.x * sin(parentTransform.rotation_rad * M_PI) +
						currentSpriteTransform.position_px.y * cos(parentTransform.rotation_rad * M_PI));
				rotationRelativeToCamera +=
					-((currentSpriteTransform.rotation_rad + parentTransform.rotation_rad -
						cameraTransform->rotation_rad) * 180.0);

				spriteID = spriteParentID;
			} while (spriteParentID != NO_PARENT);

			SDLRenderable renderable;
			renderable.texture = sprite->textureFrames.at(sprite->frameIndex).data;

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