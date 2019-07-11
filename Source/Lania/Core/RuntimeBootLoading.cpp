#include "RuntimeBootLoading.hpp"
#include <SDL_video.h>
#include <Utilities/DataStructures/String.hpp>
#include <yaml-cpp/yaml.h>

void Lania::RuntimeBootLoading::build(BootConfiguration* bootConfig, String filePath)
{
	YAML::Node runtimeBoot = YAML::LoadFile(filePath);

	for (YAML::const_iterator it1 = runtimeBoot.begin(); it1 != runtimeBoot.end(); ++it1)
	{
		if (it1->first.as<std::string>() == "application")
		{
			for (YAML::const_iterator it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
			{
				if (it2->first.as<std::string>() == "name")
					bootConfig->appName = it2->second.as<std::string>();
				else if (it2->first.as<std::string>() == "icon")
					bootConfig->icon = it2->second.as<std::string>();
				else if (it2->first.as<std::string>() == "main_scene")
					bootConfig->mainScene = it2->second.as<std::string>();
			}
		}
		if (it1->first.as<std::string>() == "application_window")
		{
			for (YAML::const_iterator it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
			{
				if (it2->first.as<std::string>() == "title")
					bootConfig->windowTitle = it2->second.as<std::string>();
				else if (it2->first.as<std::string>() == "width")
					bootConfig->windowWidth_px = it2->second.as<int>();
				else if (it2->first.as<std::string>() == "height")
					bootConfig->windowHeight_px = it2->second.as<int>();
				else if (it2->first.as<std::string>() == "fullscreen")
					bootConfig->windowFlags |= (SDL_WINDOW_FULLSCREEN & it2->second.as<bool>());
				else if (it2->first.as<std::string>() == "resizable")
					bootConfig->windowFlags |= (SDL_WINDOW_RESIZABLE & it2->second.as<bool>());
				else if (it2->first.as<std::string>() == "maximized")
					bootConfig->windowFlags |= (SDL_WINDOW_MAXIMIZED & it2->second.as<bool>());
				else if (it2->first.as<std::string>() == "rendering_api")
					bootConfig->renderingAPI = it2->second.as<std::string>();
				else if (it2->first.as<std::string>() == "target_fps")
					bootConfig->targetFPS = it2->second.as<int>();
			}
		}
	}

	if (bootConfig->renderingAPI == "opengl 3.3")
		bootConfig->windowFlags |= SDL_WINDOW_OPENGL;
	else if (bootConfig->renderingAPI == "vulkan 1.1")
		bootConfig->windowFlags |= SDL_WINDOW_VULKAN;
}
