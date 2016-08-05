#pragma once

#include "globals.h"

using boost::assign::map_list_of;

enum CategoryMasks : uint16_t
{
	TOP = 0xF000,
	MID = 0xFF00,
	LOW = 0xFFF0
};

enum CategoryID : uint16_t
{
	NoCategory           = 0x0000,

	TopLevelMask         = CategoryMasks::TOP,
	MidLevelMask         = CategoryMasks::MID,
	LowLevelMask         = CategoryMasks::LOW,

	Nevermore            = FLAGVAL(0,12),
		GameSystemModules    = Nevermore | FLAGVAL(0,8),
			DialogueSystem       = GameSystemModules | POW2(0),
			CombatSystem         = GameSystemModules | POW2(1),
			BarterSystem         = GameSystemModules | POW2(2),
			CharacterSheet       = GameSystemModules | POW2(3),
		GameEntities         = Nevermore | FLAGVAL(1,8),
			Actors               = GameEntities | FLAGVAL(0,4),
				Merchants            = Actors | POW2(0),
				VIPs                 = Actors | POW2(1),
				Extras               = Actors | POW2(2),
			Items                = GameEntities | FLAGVAL(1,4),
				KeyItems             = Items | POW2(0),
				Equipment				= Items | POW2(1),
				Usables              = Items | POW2(2),
				Trash                = Items | POW2(3),
			SetPieces            = GameEntities | FLAGVAL(2,4),
				Containers           = SetPieces | POW2(0),
				Portals              = SetPieces | POW2(1),
				Inspectables         = SetPieces | POW2(2),

		GameActions          = Nevermore | FLAGVAL(2,8),
		
	Utilities            = FLAGVAL(1,12),
		RNGUtils             = Utilities | POW2(0),
		StringUtils          = Utilities | POW2(1),
		UtilTypes            = Utilities | POW2(2),
		Interfaces           = Utilities | POW2(3),
		Errors               = Utilities | POW2(4)
};


static inline CategoryID _CatGetType(CategoryID cat, const CategoryMasks mask)
{ return (CategoryID)(cat & mask); }

static inline bool CategoryIsSubOf(CategoryID cat, const CategoryID type)
{
	return ((_CatGetType(cat, TOP) == type) || (_CatGetType(cat, MID) == type) || (_CatGetType(cat, LOW) == type));
}

typedef struct CategoryExt
{
	CategoryID _category;

	enum CatMasks : uint16_t
	{
		TOP = 0xF000,
		MID = 0xFF00,
		LOW = 0xFFF0
	};

	CategoryExt(CategoryID category): _category(category)
	{ }

	CategoryExt(): CategoryExt(NoCategory) { }

	CategoryExt& operator= (CategoryID category)
	{
		_category = category;
		return *this;
	}

	inline CategoryID _getType(const CatMasks mask)
	{ return (CategoryID)((uint16_t)_category & (uint16_t)mask);}

	inline bool isSubCategoryOf(const CategoryID type)
	{
		return ((_getType(TOP) == type) || (_getType(MID) == type) || (_getType(LOW) == type));
	}

	inline bool isNevermore()
	{ return isSubCategoryOf(Nevermore); }
	
	inline bool isUtility()
	{ return isSubCategoryOf(Utilities); }

	inline isGSM()
	{ return isSubCategoryOf(GameSystemModules); }

	inline operator CategoryID() const
	{ return _category; }



} category_x;

template<CategoryID cat>
struct CategoryType
{
	static const CategoryID CATEGORY = cat;
};


class CategoryLookup
{
#define AddLookup(x) _table[x] = #x
private:
	std::map<CategoryID, STRING> _table;
	static CategoryLookup instance;

public:
	CategoryLookup()
	{
		AddLookup(Nevermore);

		AddLookup(GameSystemModules);
		AddLookup(DialogueSystem);
		AddLookup(CombatSystem);
		AddLookup(BarterSystem);
		AddLookup(CharacterSheet);
		
		AddLookup(GameEntities);

		AddLookup(Actors);
		AddLookup(Merchants);
		AddLookup(VIPs);
		AddLookup(Extras);

		AddLookup(Items);
		AddLookup(KeyItems);
		AddLookup(Equipment);
		AddLookup(Usables);
		AddLookup(Trash);

		AddLookup(SetPieces);
		AddLookup(Containers);
		AddLookup(Portals);
		AddLookup(Inspectables);

		AddLookup(GameActions);

		AddLookup(Utilities);
		AddLookup(RNGUtils);
		AddLookup(StringUtils);
		AddLookup(UtilTypes);
		AddLookup(Interfaces);
		AddLookup(Errors);
	}

	inline STRING lookup(CategoryID cat) { return _table[cat]; }
	static inline STRING Lookup(CategoryID cat) { return instance.lookup(cat); }
};
