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
		void updateSimulationTime(int FPS);
		double calculateElapsedTime();
	};
}
