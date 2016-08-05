#pragma once

#include "rngbase.h"
#include <random>

namespace utils
{
	namespace _lib_rng
	{
		typedef std::mt19937 rint32;
		typedef std::mt19937_64 rint64;

		typedef std::uniform_real_distribution<double>  d_rfloat64;

		typedef std::uniform_int_distribution<int64_t>  d_rint64;
		typedef std::uniform_int_distribution<uint64_t> d_ruint64;

		typedef std::uniform_int_distribution<int32_t>  d_rint32;
		typedef std::uniform_int_distribution<uint32_t> d_ruint32;
	}

	class RNG : public IRNG
	{
		protected:
			_lib_rng::rint32		_src32;	
			_lib_rng::rint64		_src64;

			_lib_rng::d_rfloat64 _rlDst;
			_lib_rng::d_rint32   _btDst;

		public:
			RNG(uint_least32_t seed32, uint_least64_t seed64)
			: _src32(seed32), _src64(seed64), _btDst(0, 256)
			{ }

			RNG() : RNG(std::_Random_device(), std::_Random_device()) {}
			~RNG() { };

			int32_t next(int32_t mn, int32_t mx)
			{
				_lib_rng::d_rint32 dist(mn, mx);
				return dist(_src32);
			}
			int32_t next(int32_t mx) { return next(0, mx); }
			int32_t next() { return next(0, HIGHEST(int32_t)); }


			inline int32_t nextInt32(int32_t mn, int32_t mx) { return next(mn, mx); }
			inline int32_t nextInt32(int32_t mx) { return next(mx); }
			inline int32_t nextInt32() { return next(); }


			uint32_t nextUInt32(uint32_t mn, uint32_t mx)
			{
				_lib_rng::d_ruint32 dist(mn, mx);
				return dist(_src32);
			}
			uint32_t nextUInt32(uint32_t mx) { return nextUInt32(0, mx); }
			uint32_t nextUInt32() { return nextUInt32(0, HIGHEST(uint32_t)); }


			int64_t nextInt64(int64_t mn, int64_t mx)
			{
				_lib_rng::d_rint64 dist(mn, mx);
				return dist(_src64);
			}
			int64_t nextInt64(int64_t mx) { return nextInt64(0, mx); }
			int64_t nextInt64() { return nextInt64(0, HIGHEST(int64_t)); }


			uint64_t nextUInt64(uint64_t mn, uint64_t mx)
			{
				_lib_rng::d_ruint64 dist(mn, mx);
				return dist(_src64);
			}
			uint64_t nextUInt64(uint64_t mx) { return nextUInt64(0, mx);}
			uint64_t nextUInt64() { return nextUInt64(0, HIGHEST(uint64_t)); }


			double nextDouble(double mn, double mx)
			{
				_lib_rng::d_rfloat64 dist(mn, mx);
				return dist(_src32);
			}
			double nextDouble(double mx) { return nextDouble(0.0, mx); }
			double nextDouble() { return _rlDst(_src32); }

			template<size_t SZ>
			void nextBytes(uint8_t (&buffer)[SZ])
			{
				for (uint8_t &i : buffer)
					i = (uint8_t)(_btDst(_src32));
			}

			void nextBytes(LIST(uint8_t) &buffer)
			{
				for (uint8_t &i : buffer)
					i = (uint8_t)(_btDst(_src32));
			}

			uint8_t* nextBytes(size_t n)
			{
				uint8_t *buffer = new uint8_t[n];

				for (int i = 0; i < n; i++)
					buffer[i] = (uint8_t)(_btDst(_src32));

				return buffer;
			}
	};

	static RNG _s_rng;

}

#include "rng/rdie.h"
#include "rng/diceroller.h"
