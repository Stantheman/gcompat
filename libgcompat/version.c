#include <stdlib.h> /* getenv */

const char *gnu_get_libc_version(void)
{
	char *ver = getenv("GLIBC_FAKE_VERSION");
	if (ver == NULL) {
		ver = "2.8";
	}

	return ver;
}

const char *gnu_get_libc_release(void)
{
	return "stable";
}
