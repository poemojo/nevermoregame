#pragma once

#include "../../globals.h"

namespace utils
{
	class IDie
	{
		public:

			virtual ~IDie() = default;

			virtual void roll() = 0;
			virtual uint8_t getRoll() = 0;

			virtual inline const uint8_t sides() const = 0;
			virtual inline uint8_t value() = 0;

	};
}
