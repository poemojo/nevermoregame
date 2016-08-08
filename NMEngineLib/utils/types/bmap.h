#pragma once


#include "../../globals.h"
#include <boost/bimap.hpp>

using std::set;
using std::pair;

namespace utils
{
	template<typename _LT, typename _RT>
	using b_bimap = boost::bimap<_LT, _RT>;

	template<typename _LT, typename _RT>
	class bimap_ext
	{
	public:
		typedef _LT lf_type;
		typedef _RT rt_type;

		typedef boost::bimap<_LT, _RT> map_t;
		ctypedef map_t::value_type pos_t;

		ctypedef map_t::left_map lf_map;
		ctypedef map_t::right_map rt_map;

		ctypedef map_t::iterator iter;
		ctypedef map_t::const_iterator cn_iter;
		ctypedef map_t::reverse_iterator rev_iter;
		ctypedef map_t::const_reverse_iterator cn_rev_iter;

		ctypedef map_t::left_iterator lf_iter;
		ctypedef map_t::left_const_iterator lf_cn_iter;
		ctypedef map_t::right_iterator rt_iter;
		ctypedef map_t::right_const_iterator rt_cn_iter;
		

	};
}
