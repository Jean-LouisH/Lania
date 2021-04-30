#pragma once

#include "../rendering_api.hpp"

namespace Lania
{
	class OpenGLRenderingAPI : public RenderingAPI
	{
	public:
		~OpenGLRenderingAPI();
		RenderingAPIType getRenderingAPIType();
		const char* getRenderingAPIName();
	private:
		RenderingAPIType type = RenderingAPIType::OPENGL;
	};
}