#pragma once

#include "../../globals.h"

namespace utils
{
	class Outputable
	{
	public:
		virtual STRING _toString() = 0;
		virtual void _print() = 0;
	};

	class Formatable : public virtual Outputable
	{
	public:
		virtual void _format(const cstr) = 0;
		virtual void _format(flags_t = 0) = 0;
		virtual const cstr _format() const  = 0;

		virtual STRING _toString() = 0;
		virtual STRING _toString(const cstr) = 0;
		virtual STRING _toString(flags_t) = 0;
		
		virtual void _print() = 0;

	};
}
