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

	clearScene();

	enum
	{
		COMMENTING,
		LOADING_KEY,
		LOADING_VALUE,
		FINISHED
	};

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
	//else if (key == "input_event_map")
	//{
	//	std::string scriptSignature;
	//	std::string inputCode;
	//	std::string scriptName;
	//	std::vector<int> scriptList;
	//	int read = 0;

	//	if (value[0] == '{')
	//	{
	//		readPosition++;
	//		while (value[read] != '}')
	//		{

	//		}

	//		this->scene.keyMaps.push_back(
	//			std::pair<SDL_Keycode,
	//			std::vector<int>>(getSDLKeycode(inputCode), scriptList));
	//		this->scene.keyMaps.at(scriptCount).at(getSDLKeycode(inputCode)).at(scriptCount);
	//	}
	//	//newScene.keyMaps.blah;
	//	if (!loadedScripts.count(scriptSignature))
	//	{
	//		//this->scripts.at(scriptCount).blah;
	//		//scriptCount++;
	//	}
	//}
}

SDL_Keycode Lania::Application::getSDLKeycode(std::string inputCode)
{

}


void Lania::Application::clearScene()
{
	this->scene.dimension = 0;
	this->scene.keyMaps.clear();
}

void Lania::Application::loadScript(std::string filepath)
{
	char* scriptFileContents = File::read(filepath);
}