#pragma once

#include "../globals.h"

namespace utils
{
	template<class _Ty>
	class SortableAscending
	{
		public:
			virtual bool operator< (const _Ty&) = 0;
	};

	template<class _Ty>
	class SortableDescending
	{
		public:
			virtual bool operator> (const _Ty&) = 0;

	};

	template<class _Ty>
	class Comparable
	{
		public:
		virtual bool operator== (const _Ty&) = 0;
	};
}
