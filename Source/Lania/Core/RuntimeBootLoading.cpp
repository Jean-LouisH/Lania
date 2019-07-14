#include "RuntimeBootLoading.hpp"
#include <SDL_video.h>
#include <Utilities/DataStructures/String.hpp>
#include <yaml-cpp/yaml.h>

void Lania::RuntimeBootLoading::build(BootConfiguration* bootConfig, String filePath)
{
	try
	{
		YAML::Node runtimeBoot = YAML::LoadFile(filePath);

		for (YAML::const_iterator it0 = runtimeBoot.begin(); it0 != runtimeBoot.end(); ++it0)
		{
			if (it0->first.as<std::string>() == "application")
			{
				for (YAML::const_iterator it1 = it0->second.begin(); it1 != it0->second.end(); ++it1)
				{
					if (it1->first.as<std::string>() == "name")
						bootConfig->appName = it1->second.as<std::string>();
					else if (it1->first.as<std::string>() == "icon")
						bootConfig->icon = it1->second.as<std::string>();
					else if (it1->first.as<std::string>() == "main_scene")
						bootConfig->mainScene = it1->second.as<std::string>();
				}
			}
			if (it0->first.as<std::string>() == "application_window")
			{
				for (YAML::const_iterator it1 = it0->second.begin(); it1 != it0->second.end(); ++it1)
				{
					if (it1->first.as<std::string>() == "title")
						bootConfig->windowTitle = it1->second.as<std::string>();
					else if (it1->first.as<std::string>() == "width")
						bootConfig->windowWidth_px = it1->second.as<int>();
					else if (it1->first.as<std::string>() == "height")
						bootConfig->windowHeight_px = it1->second.as<int>();
					else if (it1->first.as<std::string>() == "fullscreen")
						bootConfig->windowFlags |= (SDL_WINDOW_FULLSCREEN & it1->second.as<bool>());
					else if (it1->first.as<std::string>() == "resizable")
						bootConfig->windowFlags |= (SDL_WINDOW_RESIZABLE & it1->second.as<bool>());
					else if (it1->first.as<std::string>() == "maximized")
						bootConfig->windowFlags |= (SDL_WINDOW_MAXIMIZED & it1->second.as<bool>());
					else if (it1->first.as<std::string>() == "rendering_api")
						bootConfig->renderingAPI = it1->second.as<std::string>();
					else if (it1->first.as<std::string>() == "target_fps")
						bootConfig->targetFPS = it1->second.as<int>();
				}
			}
		}

		if (bootConfig->renderingAPI == "opengl 3.3")
			bootConfig->windowFlags |= SDL_WINDOW_OPENGL;
		else if (bootConfig->renderingAPI == "vulkan 1.1")
			bootConfig->windowFlags |= SDL_WINDOW_VULKAN;
	}
	catch(int e)
	{
		bootConfig->windowTitle = "No Runtime Loaded";
		bootConfig->renderingAPI = "opengl 3.3";
		bootConfig->targetFPS = 30;
		bootConfig->windowFlags |= SDL_WINDOW_OPENGL;
		bootConfig->windowHeight_px = 400;
		bootConfig->windowWidth_px = 400;
	}
}
