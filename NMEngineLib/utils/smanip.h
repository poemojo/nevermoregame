#pragma once

#include "../globals.h"

using std::ostream;
using std::iostream;
using std::istream;

namespace utils
{
	class IOManipulator
	{
	public:
		template<class stream_t>
		virtual stream_t& operator() (stream_t&) const = 0;
	};

}
