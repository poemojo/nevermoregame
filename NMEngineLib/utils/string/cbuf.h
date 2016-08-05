#pragma once

#include "../../globals.h"

namespace utils
{
	template<std::size_t SZ>
	class CharBuffer
	{
		public:
			static const std::size_t ASIZE = SZ+1;
			typedef std::array<char,ASIZE> buffer_t;
			typedef buffer_t::iterator _Iter;
			typedef buffer_t::reverse_iterator _RIter;

		protected: buffer_t _buffer;

		public:
			template<std::size_t N>
			CharBuffer(cbuf<N> &raw)
			{
				std::array<char, N> tmp = raw;
				std::copy_n(tmp.begin(), _buffer.size(), _buffer.begin());
				_buffer.back() = 0;
			}
			CharBuffer(char iv)
			{
				fill(iv);
			}
			CharBuffer(): CharBuffer(0) { }

			void fill(char iv)
			{
				_buffer.fill(iv);
				_buffer.back() = 0;
			}

			bool fillFromPos(_Iter &pos, char val, bool reverse = false)
			{
				_Iter end = (reverse) ? _buffer.begin() : _buffer.end();

				auto iterate = [&reverse](_Iter it) { return (reverse) ? it-1 : it+1; };

				if (pos == end)
					return false;

				for (_Iter it = pos; it != end; it = iterate(it))
					*it = val;
				
				_buffer.back() = 0;

				return true;
				
			}

			bool fillFromChar(char search, char val, )
			{
				_Iter result = std::find(_buffer.begin(), _buffer.end(), search);
				return this->fillFromPos(result, val);
			}
			
			bool zerofill()
			




			
	};
}
