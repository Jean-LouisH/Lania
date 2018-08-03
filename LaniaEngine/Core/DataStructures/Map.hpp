/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* Map
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/LaniaEngine/blob/master/LICENSE
*/

#pragma once

#include <map>

namespace Lania
{
	template <class _Kty, class _Ty>
	using Pair = std::pair<_Kty, _Ty>;

	template <class _Kty, class _Ty>
	using Map = std::map<const _Kty, _Ty>;

	template <class _Kty, class _Ty>
	using Multimap = std::multimap<const _Kty, _Ty>;
}
