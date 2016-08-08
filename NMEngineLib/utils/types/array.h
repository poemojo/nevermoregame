#pragma once
#include "../../globals.h"

namespace utils
{
	template<typename _ET, size_t SZ>
	struct Array_t { _ET data[SZ];};

	template<size_t SZ>
	using charBuffer_t = Array_t<char, SZ>;

#if 0
	template<typename T>
	class ArrayExt
	{
		public:
			typedef T value_t, *value_p;
			CALLBACK(value_t,ValueInit);
		protected:
			size_t  _length;
			value_p _array;
		
		public:
			ArrayExt(size_t length): _length(length), _array(NULL)
			{
				if (length == 0) return;

				_array = new value_t[length];
			}
			ArrayExt(size_t length, value_t iv): ArrayExt(length)
			{
				for (value_t &elem : _array)
					elem = iv;
			}
	};
#endif
}
