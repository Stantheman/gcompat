#define _GNU_SOURCE /* program_invocation_name */
#include <errno.h>  /* program_invocation_name */
#include <stdarg.h> /* va_list, va_start, va_end */
#include <stdio.h>  /* fflush, fputc, fputs, stderr, stdout, vfprintf */
#include <string.h> /* strerror */

/**
 * Print an error message.
 *
 * LSB 5.0: LSB-Core-generic/baselib-error-n.html
 */
void error(int status, int errnum, const char *format, ...)
{
	va_list ap;

	fflush(stdout);
	fputs(program_invocation_name, stderr);
	fputs(": ", stderr);
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	if (errnum != 0) {
		fputs(": ", stderr);
		fputs(strerror(errnum), stderr);
		fputc('\n', stderr);
	}
}
