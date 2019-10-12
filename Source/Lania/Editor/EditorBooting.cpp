#include "EditorBooting.hpp"
#include <Utilities/Definitions/Constants.hpp>
#include <SDL_video.h>
#include <Utilities/GenericCollections/String.hpp>

void Lania::EditorBooting::build(BootConfiguration* bootConfig)
{
	bootConfig->appName = EDITOR_APPLICATION_NAME;
	bootConfig->windowTitle = bootConfig->appName;
	bootConfig->renderingAPI = "opengl 3.3";
	bootConfig->targetFPS = 60;
	bootConfig->windowFlags |= SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED;
	bootConfig->windowWidth_px = 1280;
	bootConfig->windowHeight_px = 720;
}