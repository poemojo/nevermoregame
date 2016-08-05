#pragma once

namespace utils
{
	typedef struct DefaultType
	{
		template<typename T>
		operator T() const { return T(); }
	}default_t;
	
	default_t const empty = default_t();
}
