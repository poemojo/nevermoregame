#pragma once

#include "../globals.h"

#include "delegate/callback.h"

namespace utils
{

	template<typename _RT, typename... Params>
	class Delegate
	{
	public:
		typedef _RT return_t;
		typedef Callback<_RT, Params...> BCB_t;
		CALLBACK(_RT, Function)(Params...);

		typedef FunctionCallback<_RT, Params...> FCB_t;
		template<class Caller>
		using MCB_t = MethodCallback<_RT, Caller, Params...>;

		template<class Caller>
		using Method_cb = typename MCB_t<Caller>::Method_cb;

	private: BCB_t *_callback;
	public:
		Delegate(Function_cb func): _callback(new FCB_t(func))
		{}

		template<class Caller>
		Delegate(Caller *obj, Method_cb<Caller> method)
			: _callback(new MCB_t<Caller>(obj, method))
		{}

		~Delegate(void)
		{}


		return_t operator()(Params... ps)
		{
			return _callback->invoke(ps...);
		}
	};
}

#include "delegate/dlgt_maker.h"
