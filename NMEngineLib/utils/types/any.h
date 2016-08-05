#pragma once

#include "../../globals.h"

namespace utils
{
	typedef struct Any
	{
		enum
		{
			Unsigned = POW2(0),
			Pointer = POW2(1)
		};

		enum typeID 
		{		
			Void = POW2(2),
			Char = POW2(3),

			Int8 = POW2(4),
			Int16 = POW2(5),
			Int32 = POW2(6),
			Int64 = POW2(7),

			Float = POW2(8),
			Double = POW2(9),

			String = Pointer | Char,
			Object = Pointer | Void,

			UChar = Unsigned | Char,
		
			UInt8 = Unsigned | Int8,
			UInt16 = Unsigned | Int16,
			UInt32 = Unsigned | Int32,
			UInt64 = Unsigned | Int64
		};

		union
		{
			char c_value;
			unsigned char uc_value;
		
			int8_t i8_value;
			int16_t i16_value;
			int32_t i32_value;
			int64_t i64_value;

			uint8_t ui8_value;
			uint16_t ui16_value;
			uint32_t ui32_value;
			uint64_t ui64_value;

			float f_value;
			double d_value;

			cstr s_value;
			void *o_value;

		};

		const typeID type;

		Any(char value): type(Char)
		{ c_value = value; }
		Any(unsigned char &value): type(UChar)
		{ uc_value = value; }

		Any(int8_t value): type(Int8)
		{ i8_value = value; }
		Any(int16_t value): type(Int16)
		{ i16_value = value; }
		Any(int32_t value): type(Int32)
		{ i32_value = value; }
		Any(int64_t value): type(Int64)
		{ i64_value = value; }

		Any(uint8_t value): type(UInt8)
		{ ui8_value = value; }
		Any(uint16_t value): type(UInt16)
		{ ui16_value = value; }
		Any(uint32_t value): type(UInt32)
		{ ui32_value = value; }
		Any(uint64_t value): type(UInt64)
		{ ui64_value = value; }

		Any(float value): type(Float)
		{ f_value = value; }
		Any(double value): type(Double)
		{ d_value = value; }

	};
}
