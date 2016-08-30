#include <dlfcn.h>	// dlsym
#include <stdio.h>	// fprintf
#include <stdlib.h>	// getenv

void *dlvsym(void *handle, char *symbol, char *version)
{
	if(getenv("GLIBC_FAKE_DEBUG"))
	{
		fprintf(stderr, "symbol %s with version %s is being redirected",
			symbol, version);
	}

	return dlsym(handle, symbol);
}
