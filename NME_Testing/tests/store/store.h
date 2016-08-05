#pragma once

#include "../../globals.h"
#include "util.h"

using std::map;
using std::string;


template<typename T>
using dict = map<string, T>;


template<class _Col>
struct IterTypes
{
	ctypedef _Col::iterator iter;
	ctypedef _Col::const_iterator cn_iter;
	ctypedef _Col::reverse_iterator rev_iter;
	ctypedef _Col::const_reverse_iterator cn_rev_iter;

	template<class T>
	struct is_iter : std::false_type {};
	template<>
	struct is_iter<iter> : std::true_type {};
	template<>
	struct is_iter<cn_iter> : std::true_type {};
	template<>
	struct is_iter<rev_iter> : std::true_type {};
	template<>
	struct is_iter<cn_rev_iter> : std::true_type {};

	template<class T, typename RT = void>
	using cen_iter_t = std::enable_if_t<is_iter<T>::value, RT>;


};

class IntStore
{
public:
	typedef dict<int> store_t;
	typedef IterTypes<store_t> its;

	ctypedef store_t::value_type pos_t;

	typedef struct cmp_val
	{
		cmp_val(int x): _x(x) { }

		bool operator() (pos_t p)
		{ return (p.second == _x); }

	private:
		int _x;
	};

private:
	store_t _data;

	void filter()
	{ rm_duplicates(_data); }

public:
	template<typename _Iter>
	IntStore(_Iter first, _Iter last): _data(first, last)
	{ filter(); }
	IntStore(store_t src): _data(src)
	{ filter(); }
	IntStore(string key, int val)
	{ _data[key] = val; }
	IntStore()
	{ }

	int& operator[] (string key)
	{ return _data[key]; }
};