#pragma once

#include "../../globals.h"

using std::enable_if_t;
using std::is_integral;

namespace utils
{
	template<typename T, bool = std::is_integral<T>::value>
	class Counter
	{ 
	public: typedef T value_t;
	protected: value_t _value;
	public:
		Counter(value_t value): _value(value) { }
		
		virtual ~Counter() { }

		virtual Counter& operator++()
		{ return *this; }
		virtual Counter operator++(int)
		{ return *this; }
		virtual Counter& operator--()
		{ return *this; }
		virtual Counter operator--(int)
		{ return *this; }

		virtual Counter& operator==(value_t value)
		{
			_value = value;
			return *this;
		}

		virtual operator value_t()
		{ return _value; }
	};

	template<typename T>
	class Counter<T, true>
	{
	public: typedef T value_t;
	protected: value_t _value;
	public:
		Counter(value_t value): _value(value)
		{}
		Counter(): Counter(0)
		{}

		virtual ~Counter() { }

		virtual Counter& operator++()
		{
			++_value;
			return *this;
		}
		virtual Counter operator++(int)
		{
			Counter temp = *this;
			++*this;
			return temp;
		}

		virtual Counter& operator--()
		{
			--_value;
			return *this;
		}
		virtual Counter operator--(int)
		{
			Counter temp = *this;
			--*this;
			return temp;
		}

		virtual Counter& operator=(value_t value)
		{
			_value = value;
			return *this;
		}

		virtual operator value_t()
		{ return _value; }
	};

	template<typename T>
	class ForwardCounter : Counter<T>
	{
	public:
		typedef Counter<T> base;
		typedef base::value_t value_t;

	protected: value_t _value;
	public:
		ForwardCounter(value_t value): base(value) { }
		ForwardCounter(): ForwardCounter(0) { }
		~ForwardCounter() { }

		ForwardCounter& operator++()
		{ return base::operator++(); }
		ForwardCounter operator++(int)
		{ return base::operator++(int); }
		
		ForwardCounter& operator--()
		{ return *this;}
		ForwardCounter operator--(int)
		{ return *this; }

		ForwardCounter& operator=(value_t value)
		{
			_value = value;
			return *this;
		}

		operator value_t()
		{ return _value; }
	};

	template<typename T>
	class BackwardCounter : Counter<T>
	{
	public:
		typedef Counter<T> base;
		typedef base::value_t value_t;
		
	protected: value_t _value;
	public:
		BackwardCounter(value_t value): base(value) { }
		BackwardCounter(): BackwardCounter(0) { }
		~BackwardCounter() { }
		
		BackwardCounter& operator++()
		{ return *this; }
		BackwardCounter operator++(int)
		{ return *this; }
		BackwardCounter& operator--()
		{ return base::operator--(); }
		BackwardCounter operator--(int)
		{ return base::operator--(int); }

		BackwardCounter& operator=(value_t value)
		{
			_value = value;
			return *this;
		}

		operator value_t()
		{
			return _value;
		}
	};

	typedef ForwardCounter<uint32_t> fwdCounter32_t;
	typedef ForwardCounter<uint16_t> fwdCounter16_t;
}
