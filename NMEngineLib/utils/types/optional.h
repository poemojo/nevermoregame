#pragma once

#include "../../globals.h"
#include <boost/optional.hpp>

using unone_t = utils::none_t;

namespace utils
{
	template<typename T>
	class optional
	{
		public:
			typedef T value_t, *value_p, &value_r, *&value_rp;
			typedef value_r &value_rv, const value_rc;
			typedef value_p *value_lp, const value_pc;

		protected:
			bool    _isInit;
			value_t _value;

		public:
			optional(): _isInit(false) { }
			optional(value_t value): _isInit(true), _value(value) { }

			inline bool isInitialized() const { return _isInit; }

			


			void value(value_t val) 
			{
				if (!_isInit)
					_isInit = true;

				_value = val;
			}
			void value(unone_t _none) { }
			
	};
}
