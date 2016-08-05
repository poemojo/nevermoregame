#pragma once

#include "../globals.h"

#define RNLen 36

using utils::AutoIncrementID;
using utils::AutoIncrementID16;
using utils::AutoIncrementID16C;
using utils::cstr;

namespace nevermore
{	
	class AB_Nevermore
	{
	public:
		static const CategoryID Category = Nevermore;
		DEFID_T(AB_Nevermore);
		#include "def/nmstatic.def"

	private:
		static ClassID Class_Code;
		RefID _id;

	protected: const STRING _name;

	public:
		AB_Nevermore(const cstr name): _name(name) { }
		AB_Nevermore(STRING name): AB_Nevermore(name.c_str()) { }

		virtual ~AB_Nevermore() = default;

		#include "def/nmvirtual.def"

		inline STRING name() const { return _name; }

		inline const uint64_t hashcode() const
		{ return ((uint64_t)(((uint64_t)classHash()) << 32)|id()); }

		inline const STRING hashcodeHex() const
		{
			uint64_t code = hashcode();
			return utils::dec2hex(code);
		}

	};

}
