#pragma once

#include "../globals.h"

using std::ios_base;
using std::fstream;
using std::queue;

namespace utils
{
	class Logger
	{
	public:
		enum LogLevel
		{
			LL_NOTICE = POW2(0), LL_WARNING = POW2(1), LL_ERROR = POW2(2),

			LD_SYSTEM = POW2(3), LD_TYPE = POW2(4), LD_VALUE = POW2(5),
			LD_OVERFLOW = POW2(6), LD_INDEX = POW2(7), LD_EOF = POW2(8),
			LD_NOTFOUND = POW2(9), LD_OS = POW2(10), LD_OTHER = POW2(11),

			NTC_SYSTEM = LL_NOTICE | LD_SYSTEM,
			WRN_SYSTEM = LL_WARNING | LD_SYSTEM,
			ERR_SYSTEM = LL_ERROR | LD_SYSTEM,

			NTC_TYPE = LL_NOTICE | LD_TYPE,
			WRN_TYPE = LL_WARNING | LD_TYPE,
			ERR_TYPE = LL_ERROR | LD_TYPE,

			NTC_VALUE = LL_NOTICE | LD_VALUE,
			WRN_VALUE = LL_WARNING | LD_VALUE,
			ERR_VALUE = LL_ERROR | LD_VALUE,

			WRN_OVERFLOW = LL_WARNING | LD_OVERFLOW,
			ERR_OVERFLOW = LL_ERROR | LD_OVERFLOW,

			NTC_INDEX = LL_NOTICE | LD_INDEX,
			WRN_INDEX = LL_WARNING | LD_INDEX,
			ERR_INDEX = LL_ERROR | LD_INDEX,

			NTC_EOF = LL_NOTICE | LD_EOF,
			WRN_EOF = LL_WARNING | LD_EOF,
			ERR_EOF = LL_ERROR | LD_EOF,

			WRN_NOTFOUND = LL_WARNING | LD_NOTFOUND,
			ERR_NOTFOUND = LL_ERROR | LD_NOTFOUND,

			NTC_OS = LL_NOTICE | LD_OS,
			WRN_OS = LL_WARNING | LD_OS,
			ERR_OS = LL_ERROR | LD_OS,

			NTC_OTHER = LL_NOTICE | LD_OTHER,
			WRN_OTHER = LL_WARNING | LD_OTHER,
			ERR_OTHER = LL_ERROR | LD_OTHER

		};

	public:
		typedef ios_base::openmode OM;
		typedef std::vector<LogLevel> LogStore;

	protected:
		fstream _file;
		LogStore _prevLogLevels;
		
	public:
		virtual ~Logger() = 0;
		
		virtual bool open(const cstr, OM = ios_base::in | ios_base::out)
		{

		}
		virtual void close() = 0;

	};
}
