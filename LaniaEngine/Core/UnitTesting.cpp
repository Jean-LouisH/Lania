#include "UnitTesting.hpp"
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(condition)											\
		if (!condition)												\
		{															\
			printf("\nAssertion failed: '%s'\n%s\nLINE:%d\n",		\
				#condition, __FILE__, __LINE__);					\
		}															\

int Lania::mainUnitTests()
{
	//ASSERT((2 > 3));
	printf("\n\nPress any key to continue");
	getchar();
	return 0;
}
