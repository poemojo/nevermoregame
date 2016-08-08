#pragma once

#include "../../globals.h"

namespace utils
{
	template<typename _Ty, typename _KT = size_t, bool isMap = false>
	class Iterable
	{
	public:
		typedef _Ty val_t;
		typedef _Ty *ptr_t;
		typedef _Ty &ref_t;
		typedef const _Ty cn_val_t;

		//Determine whether
		template<bool M> struct iter_v;
		template< > struct iter_v<false>
		{ typedef _Ty val_t; };
		template< > struct iter_v<true>
		{ typedef std::pair<const _KT, _Ty> val_t; };

		typedef iter_v<isMap>::val_t iv_t;


		typedef ra_iterator<iv_t> iter;
		typedef ra_iterator<const iv_t> cn_iter;
		typedef std::reverse_iterator<iter> rev_iter;
		typedef std::reverse_iterator<cn_iter> cn_rev_iter;

		typedef _KT key_t;
		typedef const _KT cn_key_t;
		typedef std::list<cn_key_t> keys_c;

		

		virtual inline size_t size() const = 0;
		virtual inline size_t length()
		{ return size(); }

		virtual inline key_t pos() const = 0;

		virtual inline void seek(key_t) = 0;
		virtual inline void seek(iter) = 0;
		virtual inline void seek(cn_iter) = 0;

		virtual inline key_t rpos() const = 0;
		virtual inline void rseek(key_t) = 0;
		virtual inline void rseek(rev_iter) = 0;
		virtual inline void rseek(cn_rev_iter) = 0;

		virtual inline iter begin() = 0;
		virtual inline iter end() = 0;
		virtual inline cn_iter cbegin() = 0;
		virtual inline cn_iter cend() = 0;
		virtual inline rev_iter rbegin() = 0;
		virtual inline rev_iter rend() = 0;
		virtual inline cn_rev_iter crbegin() = 0;
		virtual inline cn_rev_iter crend() = 0;

		virtual inline ref_t current() = 0;
		virtual inline ref_t next() = 0;
		virtual inline ref_t prev() = 0;

		virtual ref_t operator[] ()
	};
}
