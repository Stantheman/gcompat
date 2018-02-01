#include <dlfcn.h>  /* dlopen, dlsym */
#include <stddef.h> /* NULL */
#include <stdio.h>  /* fprintf */
#include <stdlib.h> /* getenv */

void *dlmopen(long lmid, const char *pathname, int mode)
{
	if (getenv("GLIBC_FAKE_DEBUG") != NULL) {
		fprintf(stderr,
		        "loading library %s was requested in namespace %ld",
		        pathname, lmid);
	}

	return dlopen(pathname, mode);
}

void *dlvsym(void *handle, char *symbol, char *version)
{
	if (getenv("GLIBC_FAKE_DEBUG") != NULL) {
		fprintf(stderr, "symbol %s with version %s is being redirected",
		        symbol, version);
	}

	return dlsym(handle, symbol);
}
