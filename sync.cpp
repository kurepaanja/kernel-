

#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>
#include "system.h"


int syncPrintf(const char *format, ...)
{
	int res;
	va_list args;
#ifndef BCC_BLOCK_IGNORE
	lock
		va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
	unlock
#endif
		return res;
}
