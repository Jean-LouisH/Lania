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
* Copyright (c) 2017-2020 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include <Core/Core.hpp>
#include "Scene/Scene.hpp"
#include "Native/Native.hpp"
#include <Core/Renderables.hpp>
#include "CommandLine.hpp"
#include "SceneLoader.hpp"

namespace Lania
{
	class Application
	{
	private:
		Core* core;
		Native native;
		CommandLine commandLine;
		SceneLoader sceneLoader;

		void compound2DEntityParentTransforms(
			Transform2D* finalTransform, 
			Entity2D* entities, 
			EntityID leafEntityID);
	public:
		Scene scene;
		double runtime_ms;

		void init();
		void runCommandLine();
		void interpretStartLogic();
		void interpretInputLogic();
		void interpretFrameLogic();
		void interpretComputeLogic(unsigned int computeTimeDelta_ms);
		void interpretLateLogic();
		void interpretFinalLogic();
		void buildRenderables();
		void deinit();
		Application(Core* core);
	};
}
