#pragma once

#include "../globals.h"

using std::string;
using std::endl;

using utils::AutoIncrementID16;
using utils::AutoIncrementID;
using utils::cstr;
using utils::xList;
using utils::dict;
using utils::oss;



namespace nevermore
{
	

	inline string printLength(uint16_t raw_inches)
	{
		uint16_t feet = raw_inches / 12;
		uint16_t inches = raw_inches % 12;
			

		oss << feet << "'" << std::setfill('0') << std::setw(2) << inches;
		return oss.str();
	}

	inline string printWeight(uint16_t raw_ounces)
	{
		uint16_t pounds = raw_ounces / 16;
		uint16_t ounces = raw_ounces % 16;

		oss << pounds << "lbs. " << ounces << "oz";
		return oss.str();
	}


	typedef struct EntityDescription
	{
		
	};

	class AB_GameEntity : public AB_Nevermore
	{
	public:
		static const CategoryID Category = GameEntities;
		typedef AB_Nevermore base;
		DEFID_T(AB_GameEntity);

		#include "def/nmstatic.def"
	
	private:
		static ClassID Classs_Code;
		RefID _id;

	protected:
		desc_name_t _dsc_name;
	};
}
