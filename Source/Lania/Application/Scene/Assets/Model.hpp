/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Model
*
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "../../../../ThirdParty/TinyGLTF/tinygltf 2.3.0/include/tiny_gltf.h"
#include "../../../Utilities/DataStructures/String.hpp"

namespace Lania
{
	class Model
	{
	private:
		tinygltf::Model model;
	public:
		void load(String filePath);
	};
}