#pragma once

#include "globals.h"

#define EMPTY_CONST

#define _VARG2(_1, _2, NAME, ...)             NAME
#define _VARG3(_1, _2, _3, NAME, ...)         NAME
#define _VARG4(_1, _2, _3, _4, NAME, ...)     NAME
#define _VARG5(_1, _2, _3, _4, _5, NAME, ...) NAME

#include "common/text.h"

#define  LIST1(T)   std::vector<T>
#define  LIST2(A,B) std::vector<A,B>
#define   LIST(...) _VARG2(__VA_ARGS__,LIST2,LIST1)(__VA_ARGS__)


#define  RM_PX(T)  std::remove_pointer<T>::type
#define   RM_P(T)  RM_PX(T)

#define  RM_CX(T)  std::remove_const<T>::type
#define   RM_C(T)  RM_CX(T)

#define  RM_RX(T) std::remove_reference<T>::type
#define   RM_R(T) RM_RX(T)

#define RM_CVX(T)  std::remove_cv<T>::type
#define  RM_CV(T)  RM_CVX(T)

#define  DCV_X(T)  std::declval<T>()
#define    DCV(T)  DCV_X(T)

#define RM_ALL(T)  RM_P(RM_R(RM_C(RM_CV(T))))

#define  CBPARAM(rtype, cbName, ...) rtype (*cbName)(__VA_ARGS__)
#define MCBPARAM(rtype, CName, cbName, ...) rtype (CName::*cbName)(__VA_ARGS__)
#define  CALLBACK(rtype, cbName) typedef rtype (*JOIN(cbName, cb))
#define MCALLBACK(rtype, CName, cbName) typedef rtype (SJOIN(::,CName,*JOIN(cbName, cb)))

#define   DEFID_T(T)             typedef utils::AutoIncrementID<T> RefID
#define ITERTRT_T(T)	typename std::iterator_traits<T>

#define NMNS_B(nsName) namespace nevermore { namespace nsName
#define NMNS_E(nsName) } CMT(nsName)

#define  IsMemberSame_X(Ty, member) (std::is_same<decltype(std::declval<Ty>().member), void>::value)
#define    IsMemberSame(Ty, member) IsMemberSame_X(Ty, member)
#define IsNotMemberSame(Ty, member) !IsMemberSame_X(Ty, member)

#define EnableIfT_X(test, Ty) std::enable_if_t<test, Ty>
#define   EnableIfT(test, Ty) EnableIfT_X(test, Ty)

#define  EnableIfMemberSame_X(MT, member, ET) EnableIfT(IsMemberSame(MT, member), ET)
#define EnableIfMemberNSame_X(MT, member, ET) EnableIfT(IsNotMemberSame(MT, member), ET)
#define    EnableIfMemberSame(MT, member, ET) EnableIfMemberSame_X(MT, member, ET)
#define   EnableIfMemberNSame(MT, member, ET) EnableIfMemberNSame_X(MT, member, ET)

#define MCN2(member, prefix) CONCAT(prefix, JOIN(has, member))
#define MCN1(member) MCN2(member, EMPTY_CONST)

#define MCN(...) _VARG2(__VA_ARGS__,MCN2,MCN1)(__VA_ARGS__)


#define DefineMemberScanner2(member, prefix) \
	template<typename T, typename V = bool> \
	struct MCN2(member,prefix): std::false_type {};\
	template<typename T> \
	struct MCN2(member,prefix)<T, EnableIfMemberNSame(T,CONCAT(prefix,member),bool)> : std::true_type { }

#define DefineMemberScanner1(member) DefineMemberScanner2(member, EMPTY_CONST)
#define DefineMemberScanner(...) _VARG2(__VA_ARGS__,DefineMemberScanner2,DefineMemberScanner1)(__VA_ARGS__)

#define HAS_MEMBER3(CName, member, prefix) MCN(member,prefix)<CName>::value
#define HAS_MEMBER2(CName, member) HAS_MEMBER3(CName, member, EMPTY_CONST)

#define HAS_MEMBER(...) _VARG3(__VA_ARGS__, HAS_MEMBER3, HAS_MEMBER2)(__VA_ARGS__)

#define CNTYPE_X(test, t1, t2) std::conditional_t<(test), (t1), (t2)>
#define   CNTYPE(test, t1, t2) CNTYPE_X(test, t1, t2)

#define ctypedef typedef typename

#define cusing(alias, type) using alias = typename type

#include "common/numeric.h"

template<typename T>
using ra_iterator = std::iterator<std::random_access_iterator_tag, T>;

template<typename T>
using rm_r_t = typename RM_R(T);

template<typename T>
using rm_p_t = typename RM_P(T);

template<typename T>
using rm_c_t = typename RM_C(T);

template<typename T>
using rm_cv_t = typename RM_CV(T);

template<typename T>
using rm_rp_t = rm_p_t<rm_r_t<T>>;

template<typename T>
using rm_all_t = rm_rp_t<rm_c_t<rm_cv_t<T>>>;

template<typename T>
using is_func_t = typename std::is_function<rm_rp_t<T>>::type;


template<bool _test>
using bool_t = typename std::_Cat_base<_test>::type;

template<bool _test>
using cen_true_t = std::enable_if_t<_test, void>;

template<typename T, size_t SZ>
using cen_sizeMult_t = std::enable_if_t<((SZ % BITSIZE(T)) == 0), T>;

template<class B, class T>
using cen_baseof_t = std::enable_if_t<std::is_base_of<B,T>,T>;

template<typename T>
using cen_class_t = std::enable_if_t<std::is_class<T>::value, T>;

template<typename T>
struct _Is_Vector : public std::false_type {};

template<typename T, typename... Ts>
struct _Is_Vector<LIST(T, Ts...)> : std::true_type {};

template<typename T>
struct is_vector : _Is_Vector<rm_all_t<T>> {};


template<typename _Ty, bool>
struct _Is_Callable : public is_func_t<_Ty> { };

template<typename _Ty>
struct _Is_Callable<_Ty, true>
{
	protected:
		struct Base { void operator()(); };
		struct Derived : _Ty, Base { };

		template<typename T, T> struct _Test;

		template<typename _CT> 
		static std::true_type test(...);
		template<typename _CT>
		static std::false_type test(_Test<void (Base::*)(), &_CT::operator()>*);

	public: 
		typedef decltype(test<Derived>(nullptr)) type;
		static const bool value = test<Derived>(nullptr)::value;
};


template<typename T>
using is_callable = _Is_Callable<rm_r_t<T>, std::is_class<rm_r_t<T>>::value>;

template<typename T>
using is_callable_t = typename is_callable<T>::type;

template<typename _Ty, typename... Params>
struct is_callable_sig
{
	protected:
		template<typename _CT> static auto test(_CT *obj) -> decltype((*obj)(std::declval<Params>()...), void(), std::true_type());
		template<typename _CT> static auto test(...) -> decltype(std::false_type());
	
	public:
		typedef decltype(test<_Ty>(nullptr)) type;
		static const bool value = test<_Ty>(nullptr)::value;
};

template<typename T, typename... Ps>
using is_callable_sig_t = typename is_callable_sig<T, Ps...>::type;

#if 0
namespace detail
{
	template<typename...>
	struct void_util { using type = void; };

	template<typename... _Ty>
	using void_t = typename void_util<T...>::type;

	template<typename _Ty, typename V = void>
	struct _Is_Map : std::false_type { };

	template<typename T>
	struct _Is_Map<T, void_t<typename T::key_type, 
									 typename T::mapped_type,
									 decltype(DCV(T&)[DCV(const typename T::key_type&)])>>
		: std::true_type { };
}

template<typename T>
struct is_map : detail::_Is_Map<rm_cv_t<T>> { };
#endif


namespace detail
{
	using namespace std;

	template<typename...>
	struct void_util { typedef void type; };

	template<typename... T>
	using void_t = typename void_util<T...>::type;

	template<typename T>
	struct _Is_Map : false_type { };

	template<typename _KT, typename _VT, 
		class _Cmp = less<_KT>, 
		class _Alc = allocator<pair<const _KT, _VT>>>
	struct _Is_Map<map<_KT, _VT, _Cmp, _Alc>> : true_type { }; 

	template<typename T>
	struct _Is_UMap : false_type { };

	template<typename _KT, typename _VT,
		class _Hash = hash<_KT>,
		class _Pred = equal_to<_KT>,
		class _Allc = allocator<pair<const _KT, _VT>>>
	struct _Is_UMap<unordered_map<_KT, _VT, _Hash, _Pred, _Allc>> : std::true_type { };

	template<typename T, typename U = void>
	struct has_type { typedef U type; };

	template<typename T, typename U = void>
	using has_type_t = typename has_type<T, U>::type;


	template<typename _Ty, typename Enable = void, bool isClass = is_class<_Ty>::value>
	struct is_iter : false_type {};

	template<typename _Ty>
	struct is_iter<_Ty, has_type_t<typename _Ty::iterator_category>,
		true>
		: true_type {};

}

template<typename T>
struct is_iterator : detail::is_iter<rm_cv_t<T>> {};

template<typename T, typename U = void>
using cen_iter_t = std::enable_if_t<is_iterator<T>::value, U>

template<typename T>
struct is_map : detail::_Is_Map<rm_cv_t<T>> { };
template<typename T>
struct is_map_ext : detail::_Is_Map<rm_all_t<T>> { };

template<typename T>
struct is_unordered_map : detail::_Is_UMap<rm_cv_t<T>> { };
template<typename T>
struct is_unordered_map_ext : detail::_Is_UMap<rm_all_t<T>> { };

