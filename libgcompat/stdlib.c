#include <assert.h> /* assert */
#include <limits.h> /* PATH_MAX */
#include <locale.h> /* locale_t */
#include <stddef.h> /* NULL, size_t */
#include <stdlib.h> /* getenv, realpath, strto* */
#include <unistd.h> /* get*id */

#include "alias.h"

/**
 * Resolve a pathname, with buffer overflow checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---realpath-chk-1.html
 */
char *__realpath_chk(const char *path, char *resolved_path, size_t resolved_len)
{
	assert(path != NULL);
	assert(resolved_path != NULL);
	assert(resolved_len >= PATH_MAX);

	return realpath(path, resolved_path);
}

/**
 * Get an environment variable.
 */
char *__secure_getenv(const char *name)
{
	if (geteuid() != getuid() || getegid() != getgid()) {
		return NULL;
	}

	return getenv(name);
}
weak_alias(__secure_getenv, secure_getenv);

/**
 * Underlying function for strtod.
 *
 * "__group shall be 0 or the behavior of __strtod_internal() is undefined."
 *
 * LSB 5.0: LSB-Core-generic/baselib---strtod-internal-1.html
 */
double __strtod_internal(const char *nptr, char **endptr, int group)
{
	assert(group == 0);

	return strtod(nptr, endptr);
}

/**
 * Underlying function for strtof.
 *
 * "__group shall be 0 or the behavior of __strtof_internal() is undefined."
 *
 * LSB 5.0: LSB-Core-generic/baselib---strtof-internal.html
 */
float __strtof_internal(const char *nptr, char **endptr, int group)
{
	assert(group == 0);

	return strtof(nptr, endptr);
}

/**
 * Underlying function for strtol.
 */
long __strtol_internal(const char *nptr, char **endptr, int base, int group)
{
	assert(group == 0);

	return strtol(nptr, endptr, base);
}

/**
 * Underlying function for strtold.
 *
 * "__group shall be 0 or the behavior of __strtold_internal() is undefined."
 *
 * LSB 5.0: LSB-Core-generic/baselib---strtold-internal-1.html
 */
long double __strtold_internal(const char *nptr, char **endptr, int group)
{
	assert(group == 0);

	return strtold(nptr, endptr);
}

/**
 * Convert string value to a long long integer.
 *
 * Some day, when musl supports LC_NUMERIC, we can probably remove this.
 */
long long int strtoll_l(const char *nptr, char **endptr, int base,
                        locale_t locale)
{
	return strtoll(nptr, endptr, base);
}

/**
 * Convert string value to a long long integer.
 *
 * LSB 5.0: LSB-Core-generic/baselib-strtoq-3.html
 */
long long strtoq(const char *nptr, char **endptr, int base)
{
	return strtoll(nptr, endptr, base);
}

/**
 * Convert a string to an unsigned long long.
 *
 * Some day, when musl supports LC_NUMERIC, we can probably remove this.
 */
unsigned long long int strtoull_l(const char *nptr, char **endptr, int base,
                                  locale_t locale)
{
	return strtoull(nptr, endptr, base);
}

/**
 * Convert a string to an unsigned long long.
 *
 * LSB 5.0: LSB-Core-generic/baselib-strtouq-3.html
 */
unsigned long long strtouq(const char *nptr, char **endptr, int base)
{
	return strtoull(nptr, endptr, base);
}
