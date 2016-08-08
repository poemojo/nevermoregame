#pragma once

#include "../../globals.h"

namespace utils
{
	
	typedef struct uint24_t
	{
		uint32_t value : 24;

		uint24_t(uint32_t val): value(0)
		{
			assert(val < POW2(24));
			value = val;
		}
		uint24_t(): value(0)
		{}

		uint24_t& operator= (uint32_t val)
		{
			assert(val < POW2(24));
			value = val;

			return *this;
		}

		inline bool operator== (uint32_t test) const
		{ return (value == test); }
		inline bool operator== (const uint24_t &rhs) const
		{ return (*this == rhs.value); }

		operator uint32_t()
		{ return value; }

	} uint24_t, rgbCode_t;


	template<typename _It, size_t SZ>
	struct LargeInteger
	{
		static_assert(is_unsigned<_It>::value, "LargeInteger can only be made of unsigned int fields!");
		static_assert(((SZ % BITSIZE(_It)) == 0), "LargeInteger size must be evenly divisible by field type size!");
		_It bits[SZ / BITSIZE(_It)];
	};


	template<typename _It, size_t SZ, typename = std::enable_if_t<(is_unsigned<_It>::value && !(SZ % BITSIZE(_It)))>>
	struct LargeIntegerExt
	{
		static const size_t NumFields = SZ / BITSIZE(_It);
		typedef _It int_type;
		typedef std::array<int_type, NumFields> bit_fields;

		bit_fields bits;

		LargeIntegerExt(bit_fields b): bits(b)
		{}
		LargeIntegerExt(): LargeIntegerExt(bit_fields().fill(0))
		{}

		LargeIntegerExt(size_t n, ...): LargeIntegerExt()
		{
			n = clamp(n, size_t(0), NumFields);

			va_list argv;
			va_start(argv, n);

			for (size_t i = 0; i < n; i++)
				bits[i] = va_arg(argv, int_type);

			va_end(argv);
		}

		int_type& operator[] (size_t i)
		{ return bits[i]; }

	};

	typedef struct UInt6
	{
		uint8_t _value : 6;
	} uint6_t, intBits_t;

	typedef struct BitsExt
	{
		intBits_t _data;

		static const uint8_t MIN = 1;
		static const uint8_t MAX = 64;

		BitsExt(uint8_t data): _data({0})
		{ 
			data = utils::clamp(data,MIN,MAX);
			_data = {data-1};
		}

		BitsExt(): BitsExt(0) { }

		operator uint8_t() const
		{ return ((uint8_t)(_data._value))+1; }

		BitsExt& operator= (uint8_t v)
		{
			v = utils::clamp(v,MIN,MAX);
			_data = {v-1};
			return *this;
		}
	} bits_x;


	typedef struct Scientific
	{
		static const uint32_t Base = 10;
		uint8_t power;

		Scientific(uint8_t exp): power(exp)
		{ }
		Scientific(): Scientific(0)
		{ }

		Scientific& operator= (uint8_t exp)
		{
			power = exp;
			return *this;
		}

		inline uint32_t& operator<< (uint8_t exp) const
		{
			uint32_t result = 1;
			while (--exp)
				result *= Base;

			return result;
		}

		inline operator uint32_t() const
		{ return *this<<power; }

	} scientific_t;

	static const scientific_t E; 
}

#define B10(x) (E << x)
