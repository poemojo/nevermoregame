#pragma once

#include "../globals.h"

namespace utils
{
	class IRNG
	{
		public:
			virtual ~IRNG() = default;

			virtual int32_t next(int32_t, int32_t) = 0;
			virtual int32_t next(int32_t) = 0;
			virtual int32_t next() = 0;

			virtual int64_t nextInt64(int64_t, int64_t) = 0;
			virtual int64_t nextInt64(int64_t) = 0;
			virtual int64_t nextInt64() = 0;

			virtual uint64_t nextUInt64(uint64_t, uint64_t) = 0;
			virtual uint64_t nextUInt64(uint64_t) = 0;
			virtual uint64_t nextUInt64() = 0;

			virtual inline int32_t nextInt32(int32_t, int32_t) = 0;
			virtual inline int32_t nextInt32(int32_t) = 0;
			virtual inline int32_t nextInt32() = 0;

			virtual uint32_t nextUInt32(uint32_t, uint32_t) = 0;
			virtual uint32_t nextUInt32(uint32_t) = 0;
			virtual uint32_t nextUInt32() = 0;

			virtual double nextDouble(double, double) = 0;
			virtual double nextDouble(double) = 0;
			virtual double nextDouble() = 0;

			
			template<size_t SZ>
			virtual void nextBytes(uint8_t (&)[SZ]) = 0;
			virtual void nextBytes(LIST(uint8_t)&) = 0;
			virtual uint8_t* nextBytes(size_t) = 0;

			//virtual uint8_t* nextBits(uint8_t) = 0;

	};
}
