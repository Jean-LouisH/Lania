/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Multimap
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

#include <map>

namespace Lania
{
	template <class _Kty, class _Ty>
	using Multimap = std::multimap<const _Kty, _Ty>;
}
