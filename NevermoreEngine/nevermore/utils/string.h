#pragma once

#include "../../globals.h"

using std::string;
using std::ostringstream;

NMNS_B(utils)
{
	CALLBACK(int, TransformString)(int);
	CALLBACK(std::ios_base&, BaseToggle)(std::ios_base&);

	static ostringstream oss;

	template<typename T>
	string dec2hex(T d, BaseToggle_cb toggleBase = std::noshowbase)
	{
		INT_ASSERT(T, "dec2hex first parameter must be of integral type!");
		static_assert((toggleBase == &std::showbase || toggleBase == &std::noshowbase), 
			"dec2hex second parameter must either be std::showbase or std::noshowbase!");
	
		oss << std::setfill('0') << std::setw(sizeof(T) * 2)
		    << std::hex << toggleBase << d;
		
		return oss.str();
	}

	template<size_t count>
	void s_strcpy(char (&dest)[count], const char *src)
	{
		memcpy(dest,src,sizeof(dest));
		if (dest[count-1] != 0) 
			dest[count-1] = 0;
	}

	static inline bool validate_cstr(const char *&s)
	{
		
	}

	static inline char* dup_str(const char *s)
	{
		
	}

	typedef struct CharBuffer
	{
		size_t length;
		char *buf;

		CharBuffer(size_t len)
		: length(len), buf(new char[len])
		{ }

		char& operator[] (int i)
		{
			
		};
	} charBuf_t;


}NMNS_E(utils)
