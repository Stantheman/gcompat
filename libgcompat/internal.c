#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


void GCOMPAT__panic(const char *fmt, ...)
{
	va_list va;

	fprintf(stderr, "*** gcompat panic ***\n");

	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);

	abort();
}
