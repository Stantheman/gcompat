#include <stddef.h> /* NULL */
#include <stdlib.h> /* getenv */

/**
 * Get glibc release.
 *
 * LSB 5.0: LSB-Core-generic/baselib-gnu-get-libc-version-1.html
 */
const char *gnu_get_libc_release(void)
{
	return "stable";
}

/**
 * Get glibc version.
 *
 * LSB 5.0: LSB-Core-generic/baselib-gnu-get-libc-version-1.html
 */
const char *gnu_get_libc_version(void)
{
	char *ver = getenv("GLIBC_FAKE_VERSION");

	if (ver == NULL) {
		ver = "2.8";
	}

	return ver;
}
