#pragma once

#include "../globals.h"

using std::string;
using std::ostringstream;
using std::istringstream;


namespace utils
{
	CALLBACK(int, TransformString)(int);
	CALLBACK(std::ios_base&, BaseToggle)(std::ios_base&);

	static ostringstream oss;

	typedef char *cstr;

	typedef string::iterator str_iter;
	typedef string::const_iterator const_str_iter; 
	typedef string::reverse_iterator rev_str_iter;
	typedef string::const_reverse_iterator const_rev_str_iter;

	typedef ra_iterator<char> cstr_iter;
	typedef ra_iterator<const char> const_cstr_iter;
	typedef std::reverse_iterator<cstr_iter> rev_cstr_iter;
	typedef std::reverse_iterator<const_cstr_iter> const_rev_cstr_iter;


	template<typename T, typename _Al = std::allocator<T>>
	using xList = std::vector<T, _Al>;

	template<size_t N> 
	using cbuf = char[N];

	static xList<STRING> &split(const STRING &str, char delim)
	{
		istringstream iss(str);
		xList<STRING> parts;

		STRING tok;

		while (getline(iss, tok, delim))
			parts.push_back(tok);

		return parts;
	}

	void* zeromem(void *dest, size_t n)
	{ memset(dest, 0, n); }

	template<size_t N>
	void* s_memclr(void (&dest)[N])
	{ zeromem(dest,N); }

	inline string cnd_str(bool test, string t, string f)
	{ return (test) ? t : f; }
	template<typename T>
	string dec2hex(T d, BaseToggle_cb toggleBase = &std::noshowbase)
	{
		INT_ASSERT(T, "dec2hex first parameter must be of integral type!");
		static_assert((toggleBase == &std::showbase || toggleBase == &std::noshowbase), 
			"dec2hex second parameter must either be std::showbase or std::noshowbase!");
	
		oss << std::setfill('0') << std::setw(sizeof(T) * 2)
		    << std::hex << toggleBase << d;
		
		return oss.str();
	}

	template<typename T>
	string dec2hex(T d, size_t width, BaseToggle_cb toggleBase = &std::noshowbase)
	{
		INT_ASSERT(T, "dec2hex first parameter must be of integral type!");
		static_assert((toggleBase == &std::showbase || toggleBase == &std::noshowbase),
			"dec2hex second parameter must either be std::showbase or std::noshowbase!");

		oss << std::setfill('0') << std::setw(width) << std::hex << toggleBase << d;
		return oss.str();
	}

	inline string strfmt(cstr fmt, ...)
	{
		cstr dest;
		va_list args;
		va_start(args, fmt);
		vsprintf(dest, fmt, args);
		va_end(args);
		
		return STRING(dest);
	}

	template<size_t N>
	void s_strcpy(cbuf<N> &dest, const cstr src)
	{
		strncpy(dest,src,N);
		if (dest[N-1] != 0) 
			dest[N-1] = 0;
	}

	template<size_t N>
	void s_strcpy(std::array<char, N> &dest, const cstr src)
	{
		strncpy(dest.data(), src, N);
		if (dest.back() != 0)
			dest.back() = 0;
	}

	template<size_t N>
	void s_strclr(cbuf<N> &dest)
	{ zeromem(dest, N); }


	static inline cstr dup_str(const cstr src)
	{
		if (!src) return NULL;
		size_t len = strlen(src) + 1;
		cstr dest = new char[len];
		strncpy(dest, src, len);
		
		dest[D(len)] = 0;

		return dest;
	}

	static inline cstr cut_str(const cstr src, size_t max)
	{
		cstr result = new char[I(max)];
		
		memset(result, 0, I(max));
		strncpy(result, src, max);

		result[max] = 0;

		return result;
	}

	static inline cstr strrplc(const cstr str, int pos, char chr)
	{
		int len = strlen(str);
		cstr result;

		strncpy(result, str, len);
		
		pos = clamp(pos, INV((len-2)), len-1);
		pos += (pos < 0) ? D(len) : 0;

		for (int i=pos; i<len; i++)
			result[i] = chr;

		return result;
	}




	template<size_t MAX>
	static inline cstr strrplc(char str[MAX], int pos, char chr)
	{
		char result[MAX];
		memset(result, 0, MAX);
		memcpy(result, str, D(MAX));

		pos = clamp(pos, INV((MAX-2)), MAX-1);
		pos += (pos < 0) ? D(MAX) : 0;

		for (int i=pos; i<MAX-1; i++)
			result[i] = chr;

		return result;
	}

	template<size_t MAX>
	static inline cstr rtNullPad(char str[MAX])
	{
		const cstr pch = (cstr)memchr(str,0,MAX);
		
		int pos = (pch) ? pch-str : -1;

		if (pos < 0)
			return NULL;

		return strrplc(str, pos, 0);
	}

	static inline void strtrans(STRING &str, TransformString_cb trans)
	{ std::transform(begin(str), end(str), begin(str), trans); }
	static inline STRING strtrans_d(STRING str, TransformString_cb trans)
	{
		strtrans(str, trans);
		return str;
	}
}

#include "string/cbuf.h"
#include "string/fixstr.h"
