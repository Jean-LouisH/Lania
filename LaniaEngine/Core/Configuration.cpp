#include "Configuration.hpp"
#include "SDL_video.h"
#include <string>

Lania::EngineData Config::parseInit(char* fileContent)
{
	Lania::EngineData configData;
	configData.windowFlags = 0;
	int readPosition = 0;

	std::string key = "";
	std::string value = "";

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
			fileContent[readPosition] != '\n')
		{
			value += fileContent[readPosition];
		}
		
		if (fileContent[readPosition + 1] == '\n')
		{
			if (key == "title")
			{
				configData.windowTitle = value;
			}
			else if (key == "resolution")
			{
				std::string width;
				std::string height;

				int start = 0;
				int end = value.find("x");

				width = value.substr(start, end - start);
				start = end + 1;
				end = value.find("x", start);
				height = value.substr(start, end - start);

				configData.windowWidthPixels = std::stoi(width);
				configData.windowHeightPixels = std::stoi(height);
			}
			else if (key == "rendering_api")
			{
				if (value == "OpenGL")
				{
					configData.windowFlags |= SDL_WINDOW_OPENGL;
				}
				else if (value == "Vulkan")
				{
					configData.windowFlags |= SDL_WINDOW_VULKAN;
				}
			}
			else if (key == "fullscreen")
			{
				if (value == "true")
				{
					configData.windowFlags |= SDL_WINDOW_FULLSCREEN;
				}
			}
			else if (key == "resizable")
			{
				if (value == "true")
				{
					configData.windowFlags |= SDL_WINDOW_RESIZABLE;
				}
			}
			else if (key == "maximized")
			{
				if (value == "true")
				{
					configData.windowFlags |= SDL_WINDOW_MAXIMIZED;
				}
			}
			else if (key == "main_scene")
			{
				configData.mainScene = value;
			}
		}
		readPosition++;

	} while (fileContent[readPosition] != '\0' &&
		parseState != FINISHED);

	return configData;
}
