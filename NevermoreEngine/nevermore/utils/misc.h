#pragma once
#include "../../globals.h"

using std::min;
using std::max;

NMNS_B(utils)
{
	template<typename T, size_t SZ>
	size_t getSize(T(&)[SZ])
	{ return SZ; }

	int clamp(int n, int lower, int upper)
	{  return max(lower, min(n, upper)); }

}NMNS_E(utils)
