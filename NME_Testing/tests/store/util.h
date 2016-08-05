#pragma once

#include "../../globals.h"

using std::map;

template<class Collection>
struct RemoveDuplicates
{
	ctypedef Collection::value_type val_t;

	void operator() (Collection &coll)
	{
		ctypedef Collection::value_type val_t;

		std::set<val_t> s(coll.begin(), coll.end());
		coll.assign(s.begin(), s.end());
	}
};


template<typename K, typename V>
struct RemoveDuplicates<map<K, V>>
{
	typedef map<K, V> map_t;
	ctypedef map_t::iterator iter;
	ctypedef map_t::const_iterator cn_iter;

	void operator() (map_t &coll)
	{
		std::set<V> values;

		cn_iter it = coll.cbegin();
		while (it != coll.cend())
		{
			if (values.find(it->second) != values.cend())
				coll.erase(it++);
			else
			{
				values.insert(it->second);
				++it;
			}
		}

		values.clear();
	}
};

template<class Collection>
struct RemoveDuplicatesCopy
{
	Collection operator() (Collection coll)
	{
		base(coll);
		return coll;
	}

private:
	RemoveDuplicates<Collection> base;

};

template<typename K, typename V>
struct RemoveDuplicatesCopy<map<K,V>>
{
	typedef map<K,V> map_t;
	map_t operator() (map_t coll)
	{
		base(coll);
		return coll;
	}

private:
	RemoveDuplicates<map_t> base;

};


template<class Collection>
void rm_duplicates(Collection &coll)
{
	RemoveDuplicates<Collection> rmd;

	rmd(coll);
}


template<class Collection>
Collection rm_duplicates_cp(Collection coll)
{
	RemoveDuplicatesCopy<Collection> rmdc;
	
	return rmdc(coll);
}
