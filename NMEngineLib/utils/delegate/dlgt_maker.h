#pragma once

#include "../delegate.h"

namespace utils
{
	template<typename _RT, typename... Args>
	inline static Delegate<_RT, Args...> makeDelegate(CBPARAM(_RT, func, Args...))
	{
		Delegate<_RT, Args...> d(func);
		return d;
	}

	template<class Caller, typename _RT, typename... Args>
	inline static Delegate<_RT, Args...> makeDelegate(Caller *obj, MCBPARAM(_RT, Caller, method, Args...))
	{
		Delegate<_RT, Args...> d(obj, method);
		return d;
	}
}
