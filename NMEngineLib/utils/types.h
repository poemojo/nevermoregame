#pragma once

#include "../globals.h"

namespace utils
{
	template<typename T>
	using dict = std::map<STRING, T>;

	template<typename T>
	using cdict = std::map<cstr, T>;

	typedef uint8_t flags_t;

	typedef void *void_p, **void_lp;
}

#include "types/counter.h"
#include "types/aiid.h"
#include "types/array.h"
#include "types/time.h"
#include "types/int.h"
