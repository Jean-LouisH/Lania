/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Timer
*
* Encapsulates engine and simulation time data and schedules idling.
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

namespace Lania
{
	class Timer
	{
	private:
	public:
		double engineTime;
		double simulationTime;
		double startTime;
		double currentTime;
		double sampledTime;
		void idle(int delayMilliseconds);
		void initialize();
		void updateCurrentTime();
		void updateEngineTime();
		void updateSampledTime();
		void updateSimulationTime(int frameCount, int FPS);
		double calculateElapsedTime();
	};
}
