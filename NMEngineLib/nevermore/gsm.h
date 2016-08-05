#pragma once

#include "../globals.h"
#include "nmbase.h"

using utils::AutoIncrementID;
using utils::AutoIncrementID16;
using utils::AutoIncrementID16C;
using utils::cstr;
using utils::timestamp_t;

namespace nevermore
{
	class AB_GameSystemModule : public AB_Nevermore
	{
	public:
		static const CategoryID Category = GameSystemModules;
		typedef AB_Nevermore base;
		DEFID_T(AB_GameSystemModule);

		#include "def/nmstatic.def"

	private:
		static ClassID Class_Code;
		RefID _id;

	protected: timestamp_t _timestamp;
	public:
		AB_GameSystemModule(const cstr refName): base(refName) 
		{	}
		AB_GameSystemModule(STRING refName): AB_GameSystemModule(refName.c_str()) { }

		virtual ~AB_GameSystemModule() = default;

		#include "def/nmvirtual.def"





	};
}
