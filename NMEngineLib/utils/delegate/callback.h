#pragma once

#include "../../globals.h"

namespace utils
{
	template<typename _RT, typename... Params>
	class Callback
	{
	public:
		typedef _RT return_t;

		virtual return_t invoke(Params...) = 0;
	};

	template<typename _RT, typename... Params>
	class FunctionCallback : public virtual Callback<_RT, Params...>
	{

	public:
		typedef Callback<_RT, Params...> base;
		typedef typename base::return_t return_t;

		CALLBACK(return_t, Function)(Params...);

	protected: Function_cb _function;
	public:
		FunctionCallback(Function_cb func): _function(func)
		{}

		return_t invoke(Params... ps)
		{
			return (*_function)(ps...);
		}
	};

	template<typename _RT, typename _ClTy, typename... Params>
	class MethodCallback : public virtual Callback<_RT, Params...>
	{
	public:
		typedef Callback<_RT, Params...> base;
		typedef typename base::return_t return_t;
		typedef _ClTy Caller_t;

		MCALLBACK(_RT, _ClTy, Method)(Params...);
	protected:
		void *_obj;
		Method_cb _method;

	public:
		MethodCallback(Caller_t *obj, Method_cb method): _obj(obj), _method(method)
		{}

		return_t invoke(Params... ps)
		{
			Caller_t *o = static_cast<Caller_t*>(_obj);
			return (o->*_method)(ps...);
		}
	};
}
