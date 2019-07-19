#include "Application.hpp"

void Lania::Application::init()
{
	this->scene.windowDimensions.height = core->bootConfig.windowHeight_px;
	this->scene.windowDimensions.width = core->bootConfig.windowWidth_px;
	this->scene.dataFilePath = core->bootConfig.dataFilePath;
	this->scene.load(core->bootConfig.dataFilePath + core->bootConfig.mainScene);
	this->native.init(&this->scene, this->core);
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

	renderables.layerIndices = this->scene.layerTypeList;

	for (int i = 0; i < renderables.layerIndices.size(); i++)
	{
		int currentSubscene2D = 0;
		int currentSubscene3D = 0;

		if (renderables.layerIndices.at(i) == SUBSCENE_2D)
		{
			Layer2D newLayer2D;
			Scene2D* scene2D = &this->scene.subScenes2D.at(currentSubscene2D);
			Camera2D* currentCameraComponent = &scene2D->activeCameras.at(scene2D->currentCameraIndex);
			Entity2D* currentCameraEntity = &scene2D->entities.at(currentCameraComponent->entityID);

			newLayer2D.currentCamera2D.transform_px = currentCameraEntity->transform;
			newLayer2D.currentCamera2D.viewport_px = currentCameraComponent->viewport_px;
			newLayer2D.currentCamera2D.postProcessingShaders = currentCameraEntity->shaders2D;
			
			for (int i = 0; i < scene2D->activeSprites.size(); i++)
			{
				Sprite2DRenderable sprite2D;
				Sprite2D* spriteComponent = &scene2D->activeSprites.at(i);
				Entity2D* spriteEntity = &scene2D->entities.at(spriteComponent->entityID);
				sprite2D.transform_px = spriteEntity->transform;
				sprite2D.shaders2D = spriteEntity->shaders2D;
				sprite2D.texture = spriteComponent->textureFrames.at(spriteComponent->frameIndex);
				newLayer2D.sprites2D.push_back(sprite2D);
			}

			renderables.layer2Ds.push_back(newLayer2D);
			currentSubscene2D++;
		}
		else if (renderables.layerIndices.at(i) == SUBSCENE_3D)
		{
			Layer3D newLayer3D;
			renderables.layer3Ds.push_back(newLayer3D);
			currentSubscene3D++;
		}
	}

	this->core->output.renderables = renderables;
}

Lania::Application::Application(Core* core)
{
	this->core = core;
}