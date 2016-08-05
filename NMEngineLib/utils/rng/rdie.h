#pragma once

#include "diebase.h"

namespace utils
{
	template<uint8_t MAX>
	class Die : public IDie
	{
		protected: uint8_t _value;
		public:
			static const uint8_t SIDES = MAX;

			Die(): _value(0)
			{ roll(); }
			~Die() { }
			

			void roll() { _value = (uint8_t)_s_rng.next(1, SIDES); }
			uint8_t getRoll()
			{
				roll();
				return _value;
			}

			inline const uint8_t sides() const { return SIDES; }
			inline uint8_t value() { return _value; }
			
			template<uint8_t N1, uint8_t N2>
			friend bool operator< (const Die<N1>&, const Die<N2>&);

			template<uint8_t N1, uint8_t N2>
			friend bool operator== (const Die<N1>&, const Die<N2>&);
	};
}
