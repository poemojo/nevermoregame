#pragma once

#define   SIZE std::size_t
#define   UINT unsigned int
#define USHORT unsigned short
#define  ULONG unsigned long

#define           D(x) (x-1)
#define           I(x) (x+1)
#define         INV(x) (x*-1)

#define     BITSIZE(T) (sizeof(T)*CHAR_BIT)
#define      BITMAX(nb)((1 << nb)-1)

#define      LOWEST(T) std::numeric_limits<T>::lowest()
#define     HIGHEST(T) std::numeric_limits<T>::max()
#define	  ISSIGNED(T) std::numeric_limits<T>::is_signed
#define  ISUNSIGNED(T) !(ISSIGNED(T))

#define  MXU8	HIGHEST(uint8_t)
#define  MXU16 HIGHEST(uint16_t)
#define  MXU32 HIGHEST(uint32_t)
#define  MXU64 HIGHEST(uint64_t)

#define     FLAGVAL(n, o) ((1 << n) << o)
#define        POW2(n)    (1 << n)

#define     ISINT_X(T)        std::is_integral<T>::value
#define       ISINT(T)        ISINT_X(T)
#define  ISINTEXT_X(T)			is_integral_ext<T>::value
#define    ISINTEXT(T)			ISINTEXT_X(T)
#define   INTENABLE(T, rtype) std::enable_if_t<ISINT(T), rtype>

#define  INT_ASSERT(T, message) static_assert(ISINT(T), message)
#define EINT_ASSERT(T, message) static_assert(ISINTEXT(T), message)

#define MKCLASSHASH(x, y) ((uint32_t)(((uint32_t)x)<<16)|y)
#define  MKHASHCODE(x, y) ((uint64_t)(((uint64_t)x)<<32)|y)

#define INITCOUNT(T) uint32_t utils::AutoIncrementID<T>::_count = 0

#define   MKSIGNED(T) std::make_signed<T>::type
#define MKUNSIGNED(T) std::make_unsigned<T>::type

#define BITMASK(offset, size) (((1 << (size)) - 1) << (offset))
#define GETBITS(data, offset, size) (((data) >> (offset)) & BITMASK((offset, (size))))
#define EDITBITS(data, offset, size, value) ((data) & (~BITMASK(offset, size)) | ((value) << (offset)))
#define SETBITS(data, offset, size, value) ((data) = EDITBITS((data), (offset), (size), (value)))

#define RGB_GETR(rgb) ((uint8_t)((rgb >> 16) & 0xff))
#define RGB_GETG(rgb) ((uint8_t)((rgb >> 8) & 0xff))
#define RGB_GETB(rgb) ((uint8_t)(rgb & 0xff))

#define RGB_SETR(rgb, r) ((uint32_t)(((uint32_t)(r << 16))|(rgb & 0x00ffff)))
#define RGB_SETG(rgb, g) ((uint32_t)(((uint16_t)(g << 8))|(rgb & 0xff00ff)))
#define RGB_SETB(rgb, b) ((uint32_t)(((uint8_t)b)|(rgb & 0xffff00)))

#define RGB_MAKE(r, g, b) ((uint32_t)((((uint32_t)r) << 16)|(((uint16_t)g)<< 8)|((uint8_t)b)))


template<typename T>
using is_numeric_ext = std::is_arithmetic<rm_all_t<T>>;

template<typename T>
struct is_integral_ext : std::_Is_integral<rm_all_t<T>> {};


template<typename _Ty>
struct _Is_Signed : std::false_type { };

template< >
struct _Is_Signed<int8_t> : std::true_type { };
template< >
struct _Is_Signed<int16_t> : std::true_type { };
template< >
struct _Is_Signed<int32_t> : std::true_type { };
template< >
struct _Is_Signed<int64_t> : std::true_type {};
template< >
struct _Is_Signed<char> : std::true_type {};
template< >
struct _Is_Signed<short> : std::true_type {};
template< >
struct _Is_Signed<int> : std::true_type {};
template< >
struct _Is_Signed<long> : std::true_type {};
template< >
struct _Is_Signed<long long> : std::true_type {};

template<typename T>
struct is_signed : _Is_Signed<rm_cv_t<T>> { };
template<typename T>
struct is_signed_ext : _Is_Signed<rm_all_t<T>> { };



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
template< >
struct _Is_Unsigned<unsigned char>: std::true_type {};
template< >
struct _Is_Unsigned<unsigned short>: std::true_type {};
template< >
struct _Is_Unsigned<unsigned int>: std::true_type {};
template< >
struct _Is_Unsigned<unsigned long>: std::true_type {};
template< >
struct _Is_Unsigned<unsigned long long>: std::true_type {};

template<typename T>
struct is_unsigned : _Is_Unsigned<rm_cv_t<T>> {};
template<typename T>
struct is_unsigned_ext : _Is_Unsigned<rm_all_t<T>> {};


template<typename T, typename V = T>
using cen_int_t = std::enable_if_t<std::is_integral<T>::value, V>;
template<typename T, typename V = T>
using cen_int_ext_t = std::enable_if_t<is_integral_ext<T>::value, V>;
template<typename T, typename V = T>
using cen_not_int_t = std::enable_if_t<!(ISINT(T)), V>;


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

template<bool Test, typename T, typename F>
using cn_t = typename std::conditional_t<Test, T, F>;

template<typename T, T _Val, typename = cen_unsigned_int_t<T>>
struct C
{
	static const T V = _Val;
};

template<size_t _Offset, size_t _SZ>
struct bitFieldType
{
	enum : uint64_t { Mask = BITMASK(_Offset, _SZ) };


	typedef cn_t<((uint64_t)Mask <= (uint64_t)UINT8_MAX), uint8_t, 
						cn_t<((uint64_t)Mask <= (uint64_t)UINT16_MAX), uint16_t, 
						cn_t<((uint64_t)Mask <= (uint64_t)UINT32_MAX), uint32_t, uint64_t>>> type;
};

template<size_t _Offset, size_t _SZ>
using bf_t = typename bitFieldType<_Offset, _SZ>::type;

template<typename T, size_t _Offset, size_t _Bits>
struct BitFieldEntry
{
	static_assert(_Offset + _Bits <= sizeof(T) * 8, "Member exceeds bitfield boundaries");
	static_assert(_Bits < sizeof(T) * 8, "Can't fill entire bitfield with one member");

	typedef T value_t;

	value_t value;

	static const value_t Max = (value_t(1) << _Bits) - 1;
	static const value_t Mask = Max << _Offset;

	operator value_t() const
	{ return (value >> _Offset) & Max; }



};
