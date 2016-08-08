#pragma once

#include "common.h"

#define RANDOM   POW2(0)
#define HASHCODE POW2(1)
#define SEARCH   POW2(2)

#define TEST RANDOM|HASHCODE


#ifdef TEST
	#if (TEST & RANDOM) == RANDOM

	#endif
#endif
