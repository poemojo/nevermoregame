#pragma once

#include "../globals.h"

namespace utils
{
	enum ErrorIDs
	{
		E_VALUE = POW2(0),
		E_TYPE = POW2(1),
		E_FILE = POW2(2),
		
		ED_LOW = POW2(3),
		ED_HIGH = POW2(4),
		ED_NOTFOUND = POW2(5),
		ED_WRITE = POW2(6),
		ED_READ = POW2(7),

		E_VALUE_LOW = E_VALUE | ED_LOW,
		E_VALUE_HIGH = E_VALUE | ED_LOW

	};
}
