#include "Application.hpp"

void Lania::Application::init()
{
	this->scene.windowCopy.height = core->appConfig.windowHeight_px;
	this->scene.windowCopy.width = core->appConfig.windowWidth_px;
	this->native.init(&this->scene, this->core);
	this->vm.init(&this->scene, this->core);
}

void Lania::Application::interpretStartLogic()
{
	this->native.interpretStartLogic(&this->scene, this->core);
	this->vm.interpretStartLogic(&this->scene, this->core);
}

void Lania::Application::interpretInputLogic()
{
	this->native.interpretInputLogic(&this->scene, this->core);
	this->vm.interpretInputLogic(&this->scene, this->core);
}

void Lania::Application::interpretFrameLogic()
{
	this->native.interpretFrameLogic(&this->scene, this->core);
	this->vm.interpretFrameLogic(&this->scene, this->core);
}

void Lania::Application::interpretComputeLogic(unsigned int computeTimeDelta_ms)
{
	this->native.interpretComputeLogic(&this->scene, this->core, computeTimeDelta_ms);
	this->vm.interpretComputeLogic(&this->scene, this->core, computeTimeDelta_ms);
}

void Lania::Application::interpretLateLogic()
{
	this->native.interpretLateLogic(&this->scene, this->core);
	this->vm.interpretLateLogic(&this->scene, this->core);
}

void Lania::Application::interpretFinalLogic()
{
	this->native.interpretFinalLogic(&this->scene, this->core);
	this->vm.interpretFinalLogic(&this->scene, this->core);
}

Lania::Application::Application(Core* core)
{
	this->core = core;
}