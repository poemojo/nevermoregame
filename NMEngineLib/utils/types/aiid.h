#pragma once

#include "../../globals.h"

namespace utils
{
	template<typename T>
	class AutoIncrementID
	{
	protected:
		static fwdCounter32_t _count;
		uint32_t _value;

	public:
		AutoIncrementID(): _value(0)
		{ _value = (uint32_t)(++_count); }

		~AutoIncrementID() { }

		operator uint32_t() const { return _value; }
	};

	template<typename T>
	class AutoIncrementID16
	{
	protected:
		static fwdCounter16_t _count;
		uint16_t _value;

	public:
		AutoIncrementID16(): _value(0)
		{ _value = (uint16_t)(++_count); }

		~AutoIncrementID16() { }

		operator uint16_t() const { return _value; }
	};

	template<CategoryID C>
	using AutoIncrementID16C = AutoIncrementID16<CategoryType<C>>;
}
