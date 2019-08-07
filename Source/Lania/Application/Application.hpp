/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Application
*
* The layer on top of the engine that accepts developer scripting,
* scene and asset data to define and control the game / simulation.
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Core/Core.hpp>
#include "Scene/Scene.hpp"
#include "Native/Native.hpp"
#include <Core/HAL/Renderables.hpp>

namespace Lania
{
	class Application
	{
	private:
		Core* core;
		Native native;
		void compound2DEntityParentTransforms(
			Transform2D* finalTransform, 
			Entity2D* entities, 
			EntityID leafEntityID);
		bool isWaitingOnCommand;
	public:
		Scene scene;

		void init();
		void runCommandLine();
		void interpretStartLogic();
		void interpretInputLogic();
		void interpretFrameLogic();
		void interpretComputeLogic(unsigned int computeTimeDelta_ms);
		void interpretLateLogic();
		void interpretFinalLogic();
		void buildRenderables();
		Application(Core* core);
	};
}
