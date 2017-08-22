#include "EngineConfiguration.hpp"

Lania::RuntimeData Lania::EngineConfiguration::parseInitConfig(char* fileContent)
{
	Lania::RuntimeData configData;
	int readPosition = 0;

	string key = "";
	string value = "";

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
			if (key == "Window Title")
			{
				configData.windowTitle = value;
			}
			else if (key == "Window Width")
			{
				configData.windowWidthPixels = std::stoi(value);
			}
			else if (key == "Window Height")
			{
				configData.windowHeightPixels = std::stoi(value);
			}
			else if (key == "Target FPS")
			{
				configData.targetFPS = std::stoi(value);
			}
			else if (key == "Rendering API")
			{
				;
			}
			else if (key == "Window X Position")
			{
				configData.windowXPosition = std::stoi(value);
			}
			else if (key == "Window Y Position")
			{
				configData.windowYPosition = std::stoi(value);
			}
			else if (key == "Windowed")
			{
				;
			}
		}
		readPosition++;

	} while (fileContent[readPosition] != '\0' &&
		parseState != FINISHED);

	configData.state = GAMEPLAY;
	configData.isRunning = true;

	return configData;
}
