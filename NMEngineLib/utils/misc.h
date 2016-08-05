#pragma once
#include "../globals.h"

using std::min;
using std::max;
using std::map;
using std::string;



namespace utils
{

	/************************************************************************/
	/* Test Data Types                                                      */
	/************************************************************************/
	template<typename T>
	struct _Is_Vector : public std::false_type {};

	template<typename T, typename... Ts>
	struct _Is_Vector<LIST(T, Ts...)> : std::true_type {};

	template<typename T>
	struct is_vector : _Is_Vector<typename std::remove_cv<T>::type> {};


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

			return coll;
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
	struct RemoveDuplicatesCopy<map<K, V>>
	{
		typedef map<K, V> map_t;
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


	template<typename T, size_t SZ>
	size_t getSize(T(&)[SZ])
	{
		return SZ;
	}


	template<typename... Params>
	struct argpack_store
	{ };

	template<typename... Params>
	struct argpack2tuple
	{ typedef std::tuple<Params...> type; };

	template<typename... Params>
	struct argpack2tuple<argpack_store<Params...>>
	{ typedef typename argpack2tuple<Params...>::type type; };

#if 0
	template<typename T, bool = std::is_integral<T>::value>
	struct _ClampUtil
	{
		static inline T invoke(const T& n, const T& lower, const T& upper)
		{ return 0; }
	};

	template<typename T>
	struct _ClampUtil<T, true>
	{
		static inline T invoke(const T& n, const T& lower, const T& upper)
		{ return ((n < lower) ? lower : (n > upper) ? upper : n); }
	};

	template<typename IT>
	static inline IT clamp(const IT& n, const IT& lower, const IT& upper)
	{ return _ClampUtil<IT>::invoke(n, lower, upper); }
#endif


	template<typename IT, typename = cen_numeric_ext_t<IT>>
	static inline IT clamp(IT n, IT lower, IT upper)
	{ return ((n < lower) ? lower : ((n > upper) ? upper : n)); }

	template<typename T, typename = cen_unsigned_ext_t<T>>
	static inline T limitBits(T x, uint8_t nb)
	{ return clamp(x, (T)0, (T)BITMAX(nb)); }


	template<typename T> inline bool isset(T *&t) 
	{ return (t != NULL); }

	template<class ObjType>
	bool Delete(ObjType *&obj)
	{
		if (!isset(obj))
			return false;

		delete obj;
		obj = NULL;

		return true;
	}

	template<typename ArrType>
	bool DeleteArray(ArrType *&arr)
	{
		if (!isset(arr))
			return false;

		delete[] arr;
		arr = NULL;

		return true;
	}

	template<typename ElemType>
	bool DeleteVector(LIST(ElemType) &v)
	{
		if (v.empty())
			return false;

		v.clear();
	}

	template<typename ElemType>
	bool DeleteVector(LIST(ElemType) *&v)
	{
		if (!isset(v))
			return false;

		v->clear();
		v = NULL;
		
		return true;		
	}

}
