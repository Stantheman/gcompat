#include <dlfcn.h>  /* dlopen */
#include <stdio.h>  /* fprintf */
#include <stdlib.h> /* getenv */

void *dlmopen(long lmid, const char *pathname, int mode)
{
	if (getenv("GLIBC_FAKE_DEBUG")) {
		fprintf(stderr,
		        "library %s was requested to load in %ld namespace",
		        pathname, lmid);
	}

	return dlopen(pathname, mode);
}
