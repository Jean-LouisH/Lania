#include "Application.hpp"
#include "../Core/OS/File.hpp"
#include <set>

void Lania::Application::loadScene(std::string filepath)
{
	char* sceneFileContents = File::read(filepath);
	int readPosition = 0;

	std::set<std::string> loadedScripts;
	int scriptCount = 0;

	std::string key = "";
	std::string value = "";

	this->clearScene();

	enum
	{
		LOADING_KEY,
		LOADING_VALUE,
		FINISHED
	};

	unsigned char parseState = LOADING_KEY;

	do
	{
		switch (sceneFileContents[readPosition])
		{
			case '=':
				if (parseState == LOADING_KEY)
				{
					parseState = LOADING_VALUE;
					readPosition++;
				}
				break;
			case ';':
				if (parseState == LOADING_VALUE)
				{
					key = "";
					value = "";
					parseState = LOADING_KEY;
				}
				break;
			case '+':
				if (sceneFileContents[readPosition + 1] == '+')
				{
					parseState = FINISHED;
				}
				break;
		}

		if (parseState == LOADING_KEY &&
			sceneFileContents[readPosition] != ';' &&
			sceneFileContents[readPosition] != '\n')
		{
			key += sceneFileContents[readPosition];
		}
		else if (parseState == LOADING_VALUE &&
			sceneFileContents[readPosition] != ';' &&
			sceneFileContents[readPosition] != '\n')
		{
			value += sceneFileContents[readPosition];
		}

		if (sceneFileContents[readPosition + 1] == ';')
		{
			if (key == "dimensions")
			{
				if (value == "2")
				{
					this->scene.dimension = 2;
				}
				else if (value == "3")
				{
					this->scene.dimension = 3;
				}
			}
			else if (key == "input_event_maps")
			{
				std::string inputCode;
				std::string scriptMethod;
				bool loadingString = false;
				std::vector<int> scriptList;

				if (value[0] == '(')
				{
					parseState = LOADING_KEY;

					for (int i = 1; i < value.size() && 
						!(value[i] == ')' && !loadingString); i++)
					{
						switch (value[i])
						{
							case '=':
								parseState = LOADING_VALUE;
								break;
							case ',':
								inputCode = "";
								scriptMethod = "";
								parseState = LOADING_KEY;
								break;
							case '+':
								if (value[i + 1] == '+')
								{
									parseState = FINISHED;
								}
								break;
							case '\"':
								loadingString = !loadingString;
								break;
						}

						if (parseState == LOADING_KEY &&
							value[i] != '\n')
						{
							inputCode += value[i];
						}
						else if (parseState == LOADING_VALUE &&
							loadingString &&
							value[i] != '\"' &&
							value[i] != '\n')
						{
							scriptMethod += value[i];
						}

						if (value[i + 1] == ',' || (value[i + 1] == ')' && !loadingString))
						{
							this->loadScript(scriptMethod);
							//this->scripts.
							//this->scene.keyMaps.push_back()
							//pair input and script.
						}
					}

					//this->scene.keyMaps.push_back(
					//	std::pair<SDL_Keycode,
					//	std::vector<int>>(getSDLKeycode(inputCode), scriptList));
					//this->scene.keyMaps.at(scriptCount).at(getSDLKeycode(inputCode)).at(scriptCount);
				}
				//newScene.keyMaps.blah;
				//if (!loadedScripts.count(scriptSignature))
				//{
				//	//this->scripts.at(scriptCount).blah;
				//	//scriptCount++;
				//}
			}
		}
		readPosition++;
	} while (sceneFileContents[readPosition] != '\0' &&
		parseState != FINISHED);
}

SDL_Keycode Lania::Application::getSDLKeycode(std::string inputCode)
{
	return 0;
}


void Lania::Application::clearScene()
{
	this->scene.dimension = 0;
	this->scene.keyMaps.clear();
}

unsigned int Lania::Application::loadScript(std::string filepath)
{
	char* scriptFileContents = File::read(filepath);

	//return (this->scripts.size - 1);
	return 0;
}
