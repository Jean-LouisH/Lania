/**
*                      This file is part of:
*                          Lania
*           https://jean-louish.github.io/Lania/
*
* Rich Text Label
*
* Copyright (c) 2017-2019 Jean-Louis Haywood. All rights reserved.
* License: https://github.com/Jean-LouisH/Lania/blob/master/LICENSE
*/

#pragma once

#include "Entity2D.hpp"
#include "../../../Utilities/GenericCollections/String.hpp"
#include "../Assets/Font.hpp"
#include "../../../Utilities/Mathematics/Colour.hpp"
#include "../../../Utilities/Mathematics/Vector2.hpp"

namespace Lania
{
	typedef struct RichTextLabel
	{
		EntityID entityID;
		String text;
		String BBCodeText;
		Font font;
		Colour colour;
		Vector2 shadowOffset;
		bool isBBCodeEnabled;
		bool isShadowEnabled;
		double visibility_pct;

		RichTextLabel() :
			entityID(NO_ENTITY),
			isBBCodeEnabled(true),
			isShadowEnabled(false),
			visibility_pct(100.0)
		{}
	}RichTextLabel;
}