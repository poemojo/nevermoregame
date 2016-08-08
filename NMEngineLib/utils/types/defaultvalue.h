#pragma once

#include "../../globals.h"

namespace utils
{
	template<typename _Ty, _Ty _dv>
	class default_value
	{
		public:
			typedef _Ty value_t, *value_p, &value_r, *&value_rp;
			typedef value_p *l_value_p, const c_value_p;
			typedef value_r &rv_value_r, const c_value_r;
			typedef c_value_r arg_t;

			static inline const value_t Default() const
			{ return _dv; }
			
		protected:
			value_t _value;
			bool isDefault;


						
	};
}
