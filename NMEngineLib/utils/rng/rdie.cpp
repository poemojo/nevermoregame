#include "rdie.h"


namespace utils
{
	template<uint8_t N1, uint8_t N2>
	bool operator< (const Die<N1> &one, const Die<N2> &two)
	{
		if (N1 != N2) return N1 < N2;
		return one._value < two._value;
	}

	template<uint8_t N1, uint8_t N2>
	bool operator== (const Die<N1> &one, const Die<N2> &two)
	{ return ((N1 == N2) && (one._value == two._value)); }
}
