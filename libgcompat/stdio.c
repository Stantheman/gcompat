#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <wchar.h>

size_t __fread_chk(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	assert(ptr != NULL);
	assert(stream != NULL);
	return fread(ptr, size, nmemb, stream);
}

int __printf_chk(int flag, const char *format, ...)
{
	va_list argp;
	int result;

	if(flag > 0)
	{
		assert(format != NULL);
	}

	va_start(argp, format);
	result = vprintf(format, argp);
	va_end(argp);

	return result;
}

int __fprintf_chk(FILE *stream, int flag, const char *format, ...)
{
	va_list argp;
	int result;

	if(flag > 0)
	{
		assert(stream != NULL);
		assert(format != NULL);
	}

	va_start(argp, format);
	result = vfprintf(stream, format, argp);
	va_end(argp);

	return result;
}

int __sprintf_chk(char *str, int flag, size_t strlen, const char *format, ...)
{
	va_list argp;
	int result;

	assert(strlen > 0);

	va_start(argp, format);
	result = vsnprintf(str, strlen, format, argp);
	va_end(argp);

	return result;
}

int __snprintf_chk(char *str, size_t size, int flag, size_t strlen, const char *format, ...)
{
	va_list argp;
	int result;

	if(flag > 0)
	{
		assert(format != NULL);
	}
	// must always be done per LFS
	assert(size <= strlen);

	va_start(argp, format);
	result = vsnprintf(str, size, format, argp);
	va_end(argp);

	return result;
}

int __swprintf_chk(wchar_t *wcs, size_t maxlen, int flag, size_t wcslen, const wchar_t *format, ...)
{
	va_list argp;
	int result;

	if(flag > 0)
	{
		assert(format != NULL);
	}
	// must always be done per LFS
	assert(maxlen <= wcslen);

	va_start(argp, format);
	result = vswprintf(wcs, maxlen, format, argp);
	va_end(argp);

	return result;
}

int __vasprintf_chk(char **strp, int flag, const char *fmt, va_list ap)
{
	if(flag > 0)
	{
		assert(strp != NULL);
		assert(fmt != NULL);
	}
	return vasprintf(strp, fmt, ap);
}

int __vfprintf_chk(FILE *stream, int flag, const char *format, va_list ap)
{
	if(flag > 0)
	{
		assert(stream != NULL);
		assert(format != NULL);
	}
	return vfprintf(stream, format, ap);
}

int __vsnprintf_chk(char *str, size_t size, int flag, size_t strlen, const char *format, va_list ap)
{
	if(flag > 0)
	{
		assert(format != NULL);
	}
	// must always be done per LFS
	assert(size <= strlen);
	return vsnprintf(str, size, format, ap);
}

