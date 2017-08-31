/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Performance
*
* Assesses the runtime parameters that indicate satisfactory engine performance.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

namespace Lania
{
	class Performance
	{
	private:
	public:
		double FPS;
		int passedFrames;
		float fpsRefreshDelay;
		void calculateFPS(double currentTime, double sampledTime);
	};
}
