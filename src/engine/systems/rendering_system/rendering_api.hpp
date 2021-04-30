#pragma once

#include "rendering_api_type.hpp"

namespace Lania
{
	class RenderingAPI
	{
	public:
		virtual ~RenderingAPI() = 0;
		virtual RenderingAPIType getRenderingAPIType() = 0;
		virtual const char* getRenderingAPIName() = 0;
	private:
	};

	RenderingAPI::~RenderingAPI() {};
}