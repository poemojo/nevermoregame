#pragma once

#include "../../globals.h"

namespace utils
{
	class IDiceRoller
	{
		protected:
			virtual void sort() = 0;

		public:
			virtual ~IDiceRoller() = default;

			virtual void roll() = 0;
			virtual uint16_t getRoll() = 0;
			virtual void rerollValuesOf(uint8_t) = 0;
			virtual void rerollLowest(uint8_t) = 0;
			virtual void rerollLowest() = 0;
			virtual void rerollHighest(uint8_t) = 0;
			virtual void rerollHighest() = 0;

			virtual IDiceRoller dropLowest(uint8_t) = 0;
			virtual IDiceRoller dropLowest() = 0;
			virtual IDiceRoller dropHighest(uint8_t) = 0;
			virtual IDiceRoller dropHighest() = 0;

			virtual void increment() = 0;
			virtual void decrement() = 0;
			virtual void count(uint8_t) = 0;
			virtual uint8_t count() = 0;


			virtual IDie& operator[] (int) = 0;

			virtual uint16_t value() = 0;
			
	};
}
