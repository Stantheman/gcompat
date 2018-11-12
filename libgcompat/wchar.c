#include <assert.h> /* assert */
#include <stdarg.h> /* va_list, va_start, va_end */
#include <stddef.h> /* size_t */
#include <wchar.h>  /* wchar_t, *wprintf */

int __vswprintf_chk(wchar_t *s, size_t n, int flag, size_t slen,
                    const wchar_t *format, va_list ap);

/**
 * Convert formatted wide-character output, with stack checking
 *
 * LSB 5.0: LSB-Core-generic/baselib---swprintf-chk-1.html
 */
int __swprintf_chk(wchar_t *s, size_t n, int flag, size_t slen,
                   const wchar_t *format, ...)
{
	int ret;
	va_list ap;

	va_start(ap, format);
	ret = __vswprintf_chk(s, n, flag, slen, format, ap);
	va_end(ap);

	return ret;
}

/**
 * Convert formatted wide-character output, with stack checking
 *
 * LSB 5.0: LSB-Core-generic/baselib---vswprintf-chk-1.html
 */
int __vswprintf_chk(wchar_t *s, size_t n, int flag, size_t slen,
                    const wchar_t *format, va_list ap)
{
	assert(s != NULL || n == 0);
	assert(slen >= n);
	assert(format != NULL);

	return vswprintf(s, n, format, ap);
}

/**
 * Representation of the glibc internals of wcstol(3).
 *
 * LSB 5.0: LSB-Core-generic/baselib---wcstol-internal-1.html
 */
long int __wcstol_internal(const wchar_t *nptr, wchar_t **endptr, int base,
			   int group)
{
	assert(group == 0);
	return wcstol(nptr, endptr, base);
}
