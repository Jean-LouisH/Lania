#include "Application.hpp"

void Lania::Application::init()
{
	this->scene.windowCopy.height = core->appConfig.windowHeight_px;
	this->scene.windowCopy.width = core->appConfig.windowWidth_px;
	this->native.init(&this->scene);
	this->vm.init(&this->scene);
}

void Lania::Application::interpretStartLogic()
{
	this->native.interpretStartLogic(&this->scene);
	this->vm.interpretStartLogic(&this->scene);
}

void Lania::Application::interpretInputLogic()
{
	this->native.interpretInputLogic(&this->scene);
	this->vm.interpretInputLogic(&this->scene);
}

void Lania::Application::interpretProcessLogic()
{
	this->native.interpretProcessLogic(&this->scene);
	this->vm.interpretProcessLogic(&this->scene);
}

void Lania::Application::interpretComputeLogic(unsigned int computeTimeDelta_ms)
{
	this->native.interpretComputeLogic(&this->scene, computeTimeDelta_ms);
	this->vm.interpretComputeLogic(&this->scene, computeTimeDelta_ms);
}

void Lania::Application::interpretLateLogic()
{
	this->native.interpretLateLogic(&this->scene);
	this->vm.interpretLateLogic(&this->scene);
}

void Lania::Application::interpretFinalLogic()
{
	this->native.interpretFinalLogic(&this->scene);
	this->vm.interpretFinalLogic(&this->scene);
}

Lania::Application::Application(Core* core)
{
	this->core = core;
}