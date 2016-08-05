#pragma once

#include "../../globals.h"


namespace utils
{
	template<size_t N>
	class FixedString
	{
		public: 
			static const size_t ASIZE = N+1;
			typedef std::array<char, ASIZE> buffer_t;

		private:
			buffer_t _buffer;

		public:
			//Constructor copies a fixed char array of the same size as
			//_buffer into _buffer
			FixedString(buffer_t &buf):
			{ std::copy(); }

			FixedString(const cstr src)
			{ s_strcpy(_buffer,src); }

			//std::string constructor
			FixedString(STRING src): FixedString(src.c_str())
			{ }

			template<size_t SZ>
			FixedString(const FixedString<SZ>& other): FixedString(other.c_str())
			{	}
			
			//Default Constructor
			FixedString(): FixedString("")
			{ }


			~FixedString()
			{
				delete[] _buffer;
				_buffer = NULL;
			}


			void clear()
			{ zeromem(_buffer.data(), ASIZE); }
	
			template<size_t L>
			void copyBuffer(const FixedString<L> &other)
			{ s_strcpy(_buffer, other.c_str()); }

			inline buffer_t buffer() const { return _buffer; }
			inline cstr c_str() const { return _buffer.data(); }
			inline STRING str() const { return STRING(_buffer.data()); }

			inline const size_t bufLength() const { return ASIZE; }

			FixedString& operator= (const cstr other)
			{
				s_strcpy(_buffer, other);
				_buffer.back() = 0;
				return *this;
			}

			FixedString& operator= (const FixedString& other)
			{
				*this = other.c_str();
				return *this;
			}

			friend bool operator==(const FixedString &obj, const cstr &other)
			{
				cstr one = obj._buffer;
				return (strcmp(one, other) == 0);
			}
			friend bool operator==(const FixedString &obj, const STRING &other)
			{ 
				STRING tmp = obj.str();
				return (tmp.compare(other) == 0);
			}

			template<size_t L1, size_t L2>
			friend bool operator==(const FixedString<L1> &obj, const cbuf<L2> &other)
			{
				const cstr &tmp = other;
				return ((L1 == L2) && (obj == tmp));
			}

			template<size_t L1, size_t L2>
			friend bool operator==(const FixedString<L1> &obj, const FixedString<L2> &other)
			{
				const cstr &tmp = other._buffer;
				return ((L1 == L2) && (obj == tmp));
			}

			friend bool operator!=(const FixedString& obj, const cstr &other)
			{ return (!(obj == other)); }
			friend bool operator!=(const FixedString& obj, const FixedString &other)
			{ return (!(obj == other)); }
			friend bool operator!=(const FixedString& obj, const string &other)
			{ return (!(obj == other)); }



	};

	template<size_t N>
	static inline FixedString<N> _transFxStr(const FixedString<N> obj, TransformString_cb ts)
	{
		STRING str = obj.str();
		std::transform(str.begin(), str.end(), str.begin(), ts);
		
		return FixedString<N>(str);
	}


	template<size_t N>
	static inline STRING uppercase(const FixedString<N> obj)
	{ return _transFxStr(obj, std::toupper); }

	template<size_t N>
	static inline STRING lowercase(const FixedString<N> obj)
	{ return _transFxStr(obj, std::tolower); }
}
