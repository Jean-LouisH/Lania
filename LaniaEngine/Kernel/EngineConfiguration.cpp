#include "EngineConfiguration.hpp"

Lania::RuntimeData Lania::EngineConfiguration::parseInitConfig(char* fileContent)
{
	Lania::RuntimeData configData;
	int readPosition = 0;

	string configTitle = "";

	while (fileContent[readPosition] != NULL &&
		fileContent[readPosition] != ':')
	{
		configTitle += fileContent[readPosition];
		readPosition++;
	}

	readPosition++;

	do
	{
		string key = "";
		string value = "";

		while (fileContent[readPosition] != NULL &&
			fileContent[readPosition] == '\n' || 
			fileContent[readPosition] == ' ')
		{
			readPosition++;
		}

		while (fileContent[readPosition] != NULL &&
			fileContent[readPosition] != ':')
		{
			key += fileContent[readPosition];
			readPosition++;
		}

		readPosition++;

		while (fileContent[readPosition] != NULL &&
			fileContent[readPosition] == '\n' ||
			fileContent[readPosition] == ' ')
		{
			readPosition++;
		}

		while (fileContent[readPosition] != NULL &&
			fileContent[readPosition] != '\n')
		{
			value += fileContent[readPosition];
			readPosition++;
		}

		readPosition++;

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
	} while (fileContent[readPosition] != NULL);


	return configData;
}
