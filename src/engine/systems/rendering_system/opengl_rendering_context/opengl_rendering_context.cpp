#include "opengl_rendering_context.hpp"

Lania::OpenGLRenderingAPI::~OpenGLRenderingAPI()
{

}

Lania::RenderingContextType Lania::OpenGLRenderingAPI::getRenderingAPIType()
{
	return this->type;
}

const char* Lania::OpenGLRenderingAPI::getRenderingAPIName()
{
	return "";
}