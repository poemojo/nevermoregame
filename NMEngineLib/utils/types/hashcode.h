#pragma once

#include "../../globals.h"

namespace utils
{
	typedef struct HashCode
	{
		union
		{
			struct
			{
				uint32_t _object;
				uint32_t _classcode;
			};

			uint64_t _hashcode;
		};

		HashCode(uint32_t ccode, uint32_t obj)
		: _classcode(ccode), _object(obj)
		{}
		HashCode(uint64_t hash): _hashcode(hash) {}
		HashCode(): HashCode(0) {}
		HashCode(const HashCode& other): HashCode(other._hashcode) { }

		friend inline STRING toHexString(const HashCode&);

	} hashcode_t, *hashcode_i;

	inline STRING toHexString(const HashCode &other)
	{
		oss << std::setfill('0') << std::setw(sizeof(uint64_t) * 2)
			<< std::hex << other._hashcode;

		return oss.str();
	}
}
