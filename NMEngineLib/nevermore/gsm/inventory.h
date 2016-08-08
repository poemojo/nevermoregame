#pragma once

#include "../../globals.h"

namespace nevermore
{
	class Inventory : public AB_GameSystemModule
	{
	public:
		static const CategoryID Category = CharacterSheet;
		typedef AB_GameSystemModule base;
		DEFID_T(Inventory);

	private:
		static ClassID Class_Code;
		RefID _id;
		
	};
}
