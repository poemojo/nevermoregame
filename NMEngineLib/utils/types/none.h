#pragma once

namespace utils
{
	typedef struct None
	{
		struct init {};
		explicit None(init) {}
	}none_t;

	static const none_t none({ none_t::init() });
}
