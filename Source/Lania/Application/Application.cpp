#include "Application.hpp"
#include <math.h>

void Lania::Application::init()
{
	this->scene.windowDimensions.height = core->bootConfig.windowHeight_px;
	this->scene.windowDimensions.width = core->bootConfig.windowWidth_px;
	this->scene.dataFilePath = core->bootConfig.dataFilePath;
	this->scene.load(scene.dataFilePath + core->bootConfig.mainScene);
	this->native.init(&this->scene, this->core);
	this->commandLine.isWaitingOnCommand = this->core->bootConfig.commandLineOnStart;
}

void Lania::Application::runCommandLine()
{
	this->commandLine.run(this->core, &this->scene);
}

void Lania::Application::interpretStartLogic()
{
	this->native.interpretStartLogic(&this->scene, this->core);
}

void Lania::Application::interpretInputLogic()
{
	this->native.interpretInputLogic(&this->scene, this->core);
}

void Lania::Application::interpretFrameLogic()
{
	this->native.interpretFrameLogic(&this->scene, this->core);
}

void Lania::Application::interpretComputeLogic(unsigned int computeTimeDelta_ms)
{
	this->native.interpretComputeLogic(&this->scene, this->core, computeTimeDelta_ms);
}

void Lania::Application::interpretLateLogic()
{
	this->native.interpretLateLogic(&this->scene, this->core);
}

void Lania::Application::interpretFinalLogic()
{
	this->native.interpretFinalLogic(&this->scene, this->core);
}

void Lania::Application::buildRenderables()
{
	Renderables renderables;

	renderables.layerTypeOrder = this->scene.layerTypeList;

	for (int i = 0; i < renderables.layerTypeOrder.size(); i++)
	{
		int currentSubscene2D = 0;
		int currentSubscene3D = 0;

		if (renderables.layerTypeOrder.at(i) == SUBSCENE_2D)
		{
			Layer2D newLayer2D;
			Scene2D* scene2D = &this->scene.subScenes2D.at(currentSubscene2D);
			Entity2D* entities = scene2D->entities.data();

			Camera2D* currentCameraComponent = &scene2D->activeCameras.at(scene2D->currentCameraIndex);
			Entity2D* currentCameraEntity = &entities[currentCameraComponent->entityID];

			this->compound2DEntityParentTransforms(
				&newLayer2D.currentCamera2D.transform_px, 
				entities, 
				currentCameraComponent->entityID);

			newLayer2D.currentCamera2D.transform_px.scale = currentCameraEntity->transform.scale;
			newLayer2D.currentCamera2D.viewport_px = currentCameraComponent->viewport_px;
			newLayer2D.currentCamera2D.postProcessingShaders = currentCameraEntity->shaders2D;
			
			Sprite2D* sprites = scene2D->activeSprites.data();

			for (int i = 0; i < scene2D->activeSprites.size(); i++)
			{
				Sprite2DRenderable sprite2D;
				Sprite2D* spriteComponent = &scene2D->activeSprites.at(i);
				Entity2D* spriteEntity = &scene2D->entities.at(spriteComponent->entityID);

				this->compound2DEntityParentTransforms(
					&sprite2D.transform_px, 
					entities, 
					spriteComponent->entityID);

				sprite2D.transform_px.scale = spriteEntity->transform.scale;
				sprite2D.shaders2D = spriteEntity->shaders2D;
				sprite2D.texture = spriteComponent->textureFrames.at(spriteComponent->frameIndex);
				newLayer2D.sprites2D.push_back(sprite2D);
			}

			renderables.layer2Ds.push_back(newLayer2D);
			currentSubscene2D++;
		}
		else if (renderables.layerTypeOrder.at(i) == SUBSCENE_3D)
		{
			Layer3D newLayer3D;
			renderables.layer3Ds.push_back(newLayer3D);
			currentSubscene3D++;
		}
	}

	renderables.hasChanged = (this->core->output.renderables.layerTypeOrder.size() !=
		renderables.layerTypeOrder.size());
	this->core->output.renderables = renderables;
}

void Lania::Application::compound2DEntityParentTransforms(
	Transform2D* finalTransform,
	Entity2D* entities,
	EntityID leafEntityID)
{
	EntityID parentEntityID = entities[leafEntityID].parent;
	EntityID currentEntityID = leafEntityID;

	*finalTransform = entities[leafEntityID].transform;

	while (parentEntityID != NO_ENTITY)
	{
		Transform2D parentTransform = entities[parentEntityID].transform;

		finalTransform->rotation_rad += parentTransform.rotation_rad;

		finalTransform->position_px.x = parentTransform.position_px.x +
			(finalTransform->position_px.x * cos(parentTransform.rotation_rad) -
				finalTransform->position_px.y * sin(parentTransform.rotation_rad));
		finalTransform->position_px.y = parentTransform.position_px.y +
			(finalTransform->position_px.x * sin(parentTransform.rotation_rad) +
				finalTransform->position_px.y * cos(parentTransform.rotation_rad));

		currentEntityID = parentEntityID;
		parentEntityID = entities[currentEntityID].parent;
	}
}

Lania::Application::Application(Core* core)
{
	this->core = core;
}