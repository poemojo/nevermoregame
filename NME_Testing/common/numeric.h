#pragma once
#include "../globals.h"

#define   SIZE std::size_t
#define   UINT unsigned int
#define USHORT unsigned short
#define  ULONG unsigned long



#define           D(x) (x-1)
#define           I(x) (x+1)
#define         INV(x) (x*-1)

#define   BITSIZE(T) (sizeof(T)*CHAR_BIT)

#define      LOWEST(T) std::numeric_limits<T>::lowest()
#define     HIGHEST(T) std::numeric_limits<T>::max()
#define	  ISSIGNED(T) std::numeric_limits<T>::is_signed
#define  ISUNSIGNED(T) !(ISSIGNED(T))

#define     ISINT_X(T)        std::is_integral<T>::value
#define       ISINT(T)        ISINT_X(T)
#define   INTENABLE(T, rtype) std::enable_if<ISINT(T), rtype>::type

#define  INT_ASSERT(T, message) static_assert(ISINT(T), message)

#define     FLAGVAL(n, o) ((1 << n) << o)
#define        POW2(n)    (1 << n)


#define UIB_X(N)  JOIN(CONCAT(uint,N),t)
#define   UIB(N)  UIB_X(N)

#define HC_CLSSZ 16
#define HC_CLSOFST 32
#define HCCLS_MASK 0x0000ffffffff

#define HCCLS_T UIB(HC_CLSSZ)


#define HC_MAKE(x, y) ((uint64_t)((((HCCLS_T)x) << HC_CLSOFST)|(y)))


#define HC_GETCLASS(hc) ((HCCLS_T)(hc >> HC_CLSOFST))
#define HC_SETCLASS(hc, x) ((uint64_t)((((HCCLS_T)x) << HC_CLSOFST) | ((hc) & HCCLS_MASK)))


#define HC_CLASS(...) _VARG2(__VA_ARGS__,HC_SETCLASS, HC_GETCLASS)(__VA_ARGS__)

#define UINTN(N) \
typedef struct CONCAT(UInt,N) \
{ UINT _value : N; } \
UITD(N), *UIID(N) \
typedef struct JOIN(S, UINTID(N))




template<typename T>
using is_numeric_ext = std::is_arithmetic<rm_all_t<T>>;

template<typename T>
struct is_integral_ext : std::_Is_integral<rm_all_t<T>> {};


template<typename _Ty>
struct _Is_Signed : std::false_type {};

template< >
struct _Is_Signed<int8_t>: std::true_type {};
template< >
struct _Is_Signed<int16_t>: std::true_type {};
template< >
struct _Is_Signed<int32_t>: std::true_type {};
template< >
struct _Is_Signed<int64_t>: std::true_type {};
template<typename T>
struct is_signed : _Is_Signed<rm_cv_t<T>> {};
template<typename T>
struct is_signed_ext : _Is_Signed<rm_all_t<T>> {};



template<typename _Ty>
struct _Is_Unsigned : std::false_type {};

template< >
struct _Is_Unsigned<uint8_t>: std::true_type {};
template< >
struct _Is_Unsigned<uint16_t>: std::true_type {};
template< >
struct _Is_Unsigned<uint32_t>: std::true_type {};
template< >
struct _Is_Unsigned<uint64_t>: std::true_type {};

template<typename T>
struct is_unsigned : _Is_Unsigned<rm_cv_t<T>> {};
template<typename T>
struct is_unsigned_ext : _Is_Unsigned<rm_all_t<T>> {};


template<typename T>
using cen_int_t = std::enable_if_t<std::is_integral<T>::value, T>;
template<typename T>
using cen_int_ext_t = std::enable_if_t<is_integral_ext<T>::value, T>;

template<typename T>
using cen_signed_int_t = std::enable_if_t<is_signed<T>::value, T>;
template<typename T>
using cen_signed_ext_t = std::enable_if_t<is_signed_ext<T>::value, T>;


template<typename T>
using cen_unsigned_int_t = std::enable_if_t<is_unsigned<T>::value, T>;
template<typename T>
using cen_unsigned_ext_t = std::enable_if_t<is_unsigned_ext<T>::value, T>;


template<typename T>
using cen_numeric_ext_t = std::enable_if_t<is_numeric_ext<T>::value, T>;
