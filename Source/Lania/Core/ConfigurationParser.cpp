#include "ConfigurationParser.hpp"
#include <SDL_video.h>
#include <Utilities/DataStructures/String.hpp>

Lania::AppConfig Lania::Config::parseAppConfig(char* fileContent)
{
	AppConfig appConfig;
	appConfig.windowFlags = 0;
	int readPosition = 0;

	String key = "";
	String value = "";

	enum
	{
		COMMENTING,
		LOADING_KEY,
		LOADING_VALUE,
		FINISHED
	};

	unsigned char parseState = LOADING_KEY;

	do
	{
		switch (fileContent[readPosition])
		{
		case '-':
			if (fileContent[readPosition + 1] == '-')
			{
				parseState = COMMENTING;
				readPosition++;
			}
			break;
		case '=':
			if (parseState != COMMENTING)
			{
				parseState = LOADING_VALUE;
				readPosition++;
			}
			break;
		case '\n':
			key = "";
			value = "";
			parseState = LOADING_KEY;
			break;
		case '+':
			if (fileContent[readPosition + 1] == '+')
			{
				parseState = FINISHED;
			}
			break;
		}

		if (parseState == LOADING_KEY &&
			fileContent[readPosition] != '\n')
		{
			key += fileContent[readPosition];
		}
		else if (parseState == LOADING_VALUE &&
			fileContent[readPosition] != '\n' &&
			fileContent[readPosition] != '\r')
		{
			value += fileContent[readPosition];
		}

		if (fileContent[readPosition + 1] == '\n')
		{
			if (key == "title")
			{
				appConfig.appName = value;
			}
			else if (key == "resolution")
			{
				String width;
				String height;

				int start = 0;
				int end = value.find("x");

				width = value.substr(start, end - start);
				start = end + 1;
				end = value.find("x", start);
				height = value.substr(start, end - start);

				appConfig.windowWidth_px = std::stoi(width);
				appConfig.windowHeight_px = std::stoi(height);
			}
			else if (key == "rendering_api")
			{
				if (value == "opengl 3.3")
					appConfig.windowFlags |= SDL_WINDOW_OPENGL;
				else if (value == "vulkan 1.1")
					appConfig.windowFlags |= SDL_WINDOW_VULKAN;

				appConfig.renderingAPI = value;
			}
			else if (key == "fullscreen")
			{
				if (value == "true")
				{
					appConfig.windowFlags |= SDL_WINDOW_FULLSCREEN;
				}
			}
			else if (key == "resizable")
			{
				if (value == "true")
				{
					appConfig.windowFlags |= SDL_WINDOW_RESIZABLE;
				}
			}
			else if (key == "maximized")
			{
				if (value == "true")
				{
					appConfig.windowFlags |= SDL_WINDOW_MAXIMIZED;
				}
			}
			else if (key == "target_fps")
			{
				appConfig.targetFPS = std::stoi(value);
			}
			else if (key == "main_scene")
			{
				appConfig.mainScene = value;
			}
		}
		readPosition++;

	} while (fileContent[readPosition] != '\0' &&
		parseState != FINISHED);

	return appConfig;
}
