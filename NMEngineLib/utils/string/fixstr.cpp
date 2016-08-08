#include "fixstr.h"

namespace utils
{
	template<size_t N>
	static inline FixedString<N> _transFxStr(const FixedString<N> obj, TransformString_cb ts)
	{
		STRING str = obj.str();

		std::transform(str.begin(), str.end(), str.begin(), ts);

		
	}
}
