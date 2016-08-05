#pragma once

#include <chrono>

#include "../../globals.h"

#define TSLEN 96

namespace utils
{
	typedef char tsBuffer_t[TSLEN];

	typedef struct TimeStamp
	{
		STRING *caller;
		time_t raw;
		struct tm *tm_inf;
		tsBuffer_t buffer;

		TimeStamp(): raw(time(NULL)), tm_inf(localtime(&raw)), buffer("")
		{
			create();
		}

		void create()
		{
			raw = time(NULL);
			tm_inf = localtime(&raw);

			strftime(buffer, TSLEN, "%F;%T", tm_inf);
		}

		operator cstr()
		{ return buffer; }
		operator time_t()
		{ return raw; }

	} timestamp_t;


	bool operator< (const timestamp_t &x, const timestamp_t &y)
	{ return (x.raw < y.raw); }
	bool operator<= (const timestamp_t &x, const timestamp_t &y)
	{ return (x.raw <= y.raw); }

	bool operator> (const timestamp_t &x, const timestamp_t &y)
	{ return (y < x); }
	bool operator>= (const timestamp_t &x, const timestamp_t &y)
	{ return (y <= x); }

	bool operator== (const timestamp_t &x, const timestamp_t &y)
	{ return (x.raw == y.raw); }


	class Timer
	{
	protected:
		clock_t _start, _stop;
		bool _running;

	public:
		explicit Timer(bool start_now = false)
			: _start(0), _stop(0), _running(false)
		{
			if (start_now)
				start(true);
		}

		void start(bool reset)
		{
			if (!_running)
			{
				if (reset)
					_start = clock();

				_running = true;
			}			
		}

		void stop()
		{
			if (_running)
			{
				_stop = clock();
				_running = false;
			}
		}

		double elapsed() const
		{
			return ((_running ? clock() : _stop) - _start) / CLOCKS_PER_SEC;
		}
	};
}
