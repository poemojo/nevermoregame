#pragma once

#include "globals.h"

using std::cout;
using std::endl;

class ToggleTest
{
protected:
	bool _isInit;
	
public:
	ToggleTest(bool isInit): _isInit(isInit) { }
	ToggleTest(): ToggleTest(false) { }

	template<bool IsSet = _isInit>
	void toggle()
	{
		_isInit = (_isInit == IsSet) ? !IsSet : IsSet;
	}

	void output()
	{
		cout << std::boolalpha;
		cout << "_isInit is" << _isInit << endl;
	}
};
