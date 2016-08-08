#pragma once

#include "../../globals.h"

namespace utils
{
	class StringWrapper : virtual public Iterable<char>
	{	
	public:
		typedef Iterable<char> col_inter;
		typedef StringWrapper self;
		
		typedef col_inter::val_t val_t;
		typedef col_inter::ptr_t ptr_t;
		typedef col_inter::ref_t ref_t;
		typedef col_inter::cn_val_t cn_val_t;

	protected:
		

	public:
		StringWrapper(const cstr str) { }
		StringWrapper(const STRING str) { }
		StringWrapper(STRING str, TransformString_cb trans)
		{ STRING tstr = strtrans_d(str, trans); }
		StringWrapper(const self &rhs)
		{ swap(rhs); }
		StringWrapper(): StringWrapper("")
		{ }

		virtual ~StringWrapper() = default;

		virtual void swap(const self&) = 0;

		virtual inline size_t length() const = 0;
		virtual inline size_t pos() const = 0;
		virtual void pos(size_t) = 0;

		virtual inline ref_t current() = 0;
		virtual inline ref_t next() = 0;
		virtual inline ref_t prev() = 0;

		virtual void clear() = 0;

		virtual inline STRING str() const = 0;
		virtual inline cstr c_str() const = 0;


		virtual self& operator= (const self&) = 0;
		virtual self& operator= (const cstr) = 0;
		virtual self& operator= (const STRING) = 0;

	
		virtual operator cstr() const = 0;
		virtual operator STRING() const = 0;

		////////////////////////////////////////////////
		// @TODO Include Friend Relational Operators  //
		//   ......operator== (std::string)           //
		//   ......operator== (cstr)                  //
		//   ......operator== (StringWrapper)         //
		// .......................................... //
		//   ......operator!= (std::string)           //
		//   ......operator!= (cstr)                  //
		//   ......operator!= (StringWrapper)         //
		// .......................................... //
		//   ......operator< (std::string)            //
		//   ......operator< (cstr)                   //
		//   ......operator< (StringWrapper)          //
		// .......................................... //
		//   ......operator> (std::string)            //
		//   ......operator> (cstr)                   //
		//   ......operator> (StringWrapper)          //
		// .......................................... //
		//   ......operator<= (std::string)           //
		//   ......operator<= (cstr)                  //
		//   ......operator<= (StringWrapper)         //
		// .......................................... //
		//   ......operator>= (std::string)           //
		//   ......operator>= (cstr)                  //
		//   ......operator>= (StringWrapper)         //
		////////////////////////////////////////////////
	
	};
}
