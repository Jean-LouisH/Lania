/**
*                      This file is part of:
*                          Lania Engine
*           https://jean-louish.github.io/LaniaEngine/
*
* String
*
* Copyright (c) 2017 Jean-Louis Haywood. All rights reserved.
*/

#pragma once

namespace Lania
{
	typedef struct String
	{
		char* data;
		int length;
		int capacity;

		void clear();
		void appendChar(const char character);
		void appendCharArray(const char* charArray);
		void appendString(const String string);

		void operator+=(const char character)
		{
			appendChar(character);
		}

		void operator+=(const char* charArray)
		{
			appendCharArray(charArray);
		}

		void operator+=(const String string)
		{
			appendString(string);
		}
	}String;
}
