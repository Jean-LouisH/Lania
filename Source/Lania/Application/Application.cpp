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

Lania::Renderables Lania::Application::buildRenderables()
{
	Renderables renderables;

	return renderables;
}

Lania::Application::Application(Core* core)
{
	this->core = core;
}