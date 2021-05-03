#pragma once

#include "rendering_context_type.hpp"

namespace Lania
{
	class RenderingContext
	{
	public:
		virtual ~RenderingContext() = 0;
		virtual RenderingContextType getRenderingAPIType() = 0;
		virtual const char* getRenderingAPIName() = 0;
	private:
	};

	RenderingContext::~RenderingContext() {};
}