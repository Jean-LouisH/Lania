#pragma once

#include "../rendering_context.hpp"

namespace Lania
{
	class OpenGLRenderingAPI : public RenderingContext
	{
	public:
		~OpenGLRenderingAPI();
		virtual RenderingContextType getRenderingAPIType() override;
		virtual const char* getRenderingAPIName() override;
	private:
		RenderingContextType type = RenderingContextType::OPENGL;
	};
}