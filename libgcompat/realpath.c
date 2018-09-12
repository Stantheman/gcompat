#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef LINKER
#error LINKER must be defined
#endif

static char *(*real_realpath)(const char *restrict, char *restrict);

char *realpath(const char *restrict path, char *restrict resolved)
{
	if (real_realpath == NULL) {
		real_realpath = dlsym(RTLD_NEXT, "realpath");
		if (real_realpath == NULL) {
			errno = ENOSYS;
			return NULL;
		}
	}

	if (!strcmp(path, "/proc/self/exe")) {
		char *fixed = resolved;

		if (fixed == NULL) {
			fixed = malloc(PATH_MAX);
			if (fixed == NULL) {
				errno = ENOMEM;
				return NULL;
			}
		}

		/* If passed in, the buffer is at least PATH_MAX per POSIX. */
		ssize_t written = readlink(path, fixed, PATH_MAX - 1);
		if (written == -1) {
			/* Free the buffer iff we allocated it. */
			if (fixed != resolved)
				free(fixed);
			return NULL;
		}
		fixed[written] = '\0';

		return fixed;
	}

	return real_realpath(path, resolved);
}
