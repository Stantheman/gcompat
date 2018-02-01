#define _GNU_SOURCE /* fgets_unlocked */
#include <assert.h> /* assert */
#include <stdarg.h> /* va_list, va_start, va_end */
#include <stddef.h> /* NULL, size_t */
#include <stdio.h>  /* feof, fgets, fread, puts, v*printf */

int __vasprintf_chk(char **strp, int flag, const char *format, va_list ap);
int __vfprintf_chk(FILE *stream, int flag, const char *format, va_list ap);
int __vsnprintf_chk(char *s, size_t n, int flag, size_t slen,
                    const char *format, va_list ap);
int __vsprintf_chk(char *s, int flag, size_t slen, const char *format,
                   va_list ap);

/**
 * Test end-of-file indicator on a stream.
 *
 * LSB 5.0: LSB-Core-generic/baselib--io-feof-3.html
 */
int _IO_feof(FILE *stream)
{
	return feof(stream);
}

/**
 * Put a string on standard output.
 *
 * LSB 5.0: LSB-Core-generic/baselib--io-puts-3.html
 */
int _IO_puts(const char *c)
{
	return puts(c);
}

/**
 * Print to allocated string, with stack checking.
 */
int __asprintf_chk(char **strp, int flag, const char *format, ...)
{
	int ret;
	va_list ap;

	va_start(ap, format);
	ret = __vasprintf_chk(strp, flag, format, ap);
	va_end(ap);

	return ret;
}

/**
 * String input, with buffer overflow checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---fgets-chk-1.html
 */
char *__fgets_chk(char *s, size_t slen, int n, FILE *stream)
{
	assert(s != NULL);
	assert(slen >= (size_t) n);
	assert(n > 0);
	assert(stream != NULL);

	return fgets(s, n, stream);
}

/**
 * Non-locking string input, with buffer overflow checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---fgets-unlocked-chk-1.html
 */
char *__fgets_unlocked_chk(char *s, size_t slen, int n, FILE *stream)
{
	assert(s != NULL);
	assert(slen >= (size_t) n);
	assert(n > 0);
	assert(stream != NULL);

	return fgets_unlocked(s, n, stream);
}

/**
 * Convert formatted output, with stack checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---fprintf-chk-1.html
 */
int __fprintf_chk(FILE *stream, int flag, const char *format, ...)
{
	int ret;
	va_list ap;

	va_start(ap, format);
	ret = __vfprintf_chk(stream, flag, format, ap);
	va_end(ap);

	return ret;
}

/**
 * Binary input, with stack checking.
 */
size_t __fread_chk(void *buf, size_t buflen, size_t size, size_t nitems,
                   FILE *stream)
{
	assert(buf != NULL);
	assert(size > 0);
	assert(buflen / size >= nitems);
	assert(stream != NULL);

	return fread(buf, size, nitems, stream);
}

/**
 * Format and print data, with stack checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---printf-chk-1.html
 */
int __printf_chk(int flag, const char *format, ...)
{
	int ret;
	va_list ap;

	va_start(ap, format);
	ret = __vfprintf_chk(stdout, flag, format, ap);
	va_end(ap);

	return ret;
}

/**
 * Convert formatted output, with buffer overflow checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---snprintf-chk-1.html
 */
int __snprintf_chk(char *s, size_t n, int flag, size_t slen, const char *format,
                   ...)
{
	int ret;
	va_list ap;

	va_start(ap, format);
	ret = __vsnprintf_chk(s, n, flag, slen, format, ap);
	va_end(ap);

	return ret;
}

/**
 * Convert formatted output, with stack checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---sprintf-chk-1.html
 */
int __sprintf_chk(char *s, int flag, size_t slen, const char *format, ...)
{
	int ret;
	va_list ap;

	va_start(ap, format);
	ret = __vsprintf_chk(s, flag, slen, format, ap);
	va_end(ap);

	return ret;
}

/**
 * Print to allocated string, with stack checking.
 */
int __vasprintf_chk(char **strp, int flag, const char *format, va_list ap)
{
	assert(strp != NULL);
	assert(format != NULL);

	return vasprintf(strp, format, ap);
}

/**
 * Convert formatted output, with stack checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---vfprintf-chk-1.html
 */
int __vfprintf_chk(FILE *stream, int flag, const char *format, va_list ap)
{
	assert(stream != NULL);
	assert(format != NULL);

	return vfprintf(stream, format, ap);
}

/**
 * Convert formatted output, with stack checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---vprintf-chk-1.html
 */
int __vprintf_chk(int flag, const char *format, va_list ap)
{
	return __vfprintf_chk(stdout, flag, format, ap);
}

/**
 * Convert formatted output, with stack checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---vsnprintf-chk-1.html
 */
int __vsnprintf_chk(char *s, size_t n, int flag, size_t slen,
                    const char *format, va_list ap)
{
	assert(s != NULL || n == 0);
	assert(slen >= n);
	assert(format != NULL);

	return vsnprintf(s, n, format, ap);
}

/**
 * Convert formatted output, with stack checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---vsprintf-chk-1.html
 */
int __vsprintf_chk(char *s, int flag, size_t slen, const char *format,
                   va_list ap)
{
	assert(s != NULL);
	assert(slen > 0);
	assert(format != NULL);

	return vsprintf(s, format, ap);
}

/**
 * Create a name for a temporary file.
 */
char *tmpnam_r(char *s)
{
	if (s == NULL) {
		return NULL;
	}

	return tmpnam(s);
}
