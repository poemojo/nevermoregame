#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <type_traits>

#include <iostream>
#include <iomanip>
#include <sstream>

#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cctype>
#include <cinttypes>

#define STRING std::string
#define   SIZE std::size_t
#define   UINT unsigned int
#define USHORT unsigned short
#define  ULONG unsigned long
#define LIST(T) std::vector<T>


#define    QUOTE_X(x)    #x
#define      QUOTE(x)    QUOTE_X(x)

#define   CONCAT_X(x, y) x ## y
#define     CONCAT(x, y) CONCAT_X(x, y)
#define     DCAT_X(x)    x ## x
#define       DCAT(x)    DCAT_X(x)

#define     JOIN_X(x, y) x ## _ ## y
#define       JOIN(x, y) JOIN_X(x, y)

#define      CMT_X(str)  JOIN(DCAT(/), str)
#define        CMT(str)  CMT_X(str)


#define   CALLBACK(rtype, cbName) typedef rtype (*JOIN(cbName, cb))

#define    DEFID_T(T) typedef nevermore::AutoIncrementID<T> RefID

#define    ISINT_X(T) std::is_integral<T>::value
#define      ISINT(T) ISINT_X(T)

#define INT_ASSERT(T, message) static_assert(ISINT(T), message)

#define NMNS_B(nsName) namespace nevermore { namespace nsName
#define NMNS_E(nsName) } CMT(nsName)
