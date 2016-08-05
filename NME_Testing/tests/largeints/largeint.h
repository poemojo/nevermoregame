#pragma once

#include "../../globals.h"


template<typename _It, size_t _len, typename = cen_unsigned_int_t<_It>, typename = cen_sizeMult_t<_It,_len>>
struct LargeInteger
{
	static const size_t NumFields = _len / BITSIZE(_It);
	typedef _It bit_fields[NumFields];

	bit_fields bits;

};
