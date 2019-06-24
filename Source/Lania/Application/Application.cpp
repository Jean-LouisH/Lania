#include "Application.hpp"

void Lania::Application::initializeLogic()
{
	this->scene.windowCopy.height = core->appConfig.windowHeight_px;
	this->scene.windowCopy.width = core->appConfig.windowWidth_px;
	this->native.initializeLogic(&this->scene);
	this->vm.initializeLogic(&this->scene);
}

void Lania::Application::processInputs()
{
	this->native.processInputs(&this->scene);
	this->vm.processInputs(&this->scene);
}

void Lania::Application::interpretLogic()
{
	this->native.interpretLogic(&this->scene);
	this->vm.interpretLogic(&this->scene);
}

Lania::Application::Application(Core* core)
{
	this->core = core;
}