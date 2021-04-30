#include "opengl_rendering_api.hpp"

Lania::OpenGLRenderingAPI::~OpenGLRenderingAPI()
{

}

Lania::RenderingAPIType Lania::OpenGLRenderingAPI::getRenderingAPIType()
{
	return this->type;
}

const char* Lania::OpenGLRenderingAPI::getRenderingAPIName()
{
	return "";
}