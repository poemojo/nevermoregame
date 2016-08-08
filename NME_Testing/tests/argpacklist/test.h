#pragma once

#include "property.h"

typedef std::size_t sz_t;
using std::tuple;
using std::tuple_element;

typedef struct None
{
	struct init {};
	explicit None(init) {}
}none_t;

static const none_t none({ none_t::init() });

template<typename, sz_t, typename = void>
struct argpack_type
{
	typedef none_t type;
};

template<typename R, typename... Params, sz_t N>
struct argpack_type<R(Params...), N, std::enable_if_t<N <= (sizeof...(Params))>>
{
	using type = typename tuple_element<N, tuple<R, Params...>>::type;
};


template<
