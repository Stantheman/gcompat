#include <assert.h>       /* assert */
#include <dlfcn.h>        /* dlsym, RTLD_NEXT */
#include <stdlib.h>       /* NULL */
#include <string.h>       /* memcpy */
#include <sys/resource.h> /* setrlimit, struct rlimit */

/* Sigh.
 * Valve compiled Steam against the glibc2.2 version of setrlimit.
 * This broken version aliased 0 to RLIM_INFINITY.
 *
 * So, what you have to do is: if you want to run steam with this gcompat,
 * ensure you compile *without* defining NO_BROKEN_SHADOW_SETRLIMIT.
 * If you do *not* want to run steam with this gcompat, define it.
 *
 * The only problem with enabling this all the time is that if a binary
 * really does need a ulimit to be 0 for any reason (such as coredumps), it
 * very obviously won't work here.
 */
#ifndef NO_BROKEN_SHADOW_SETRLIMIT
static int (*real_rlimit)(int, const struct rlimit *);

int setrlimit(int resource, const struct rlimit *rlim)
{
	struct rlimit my_rlim;

	if (real_rlimit == NULL) {
		real_rlimit = dlsym(RTLD_NEXT, "setrlimit");
		assert(real_rlimit);
	}
	memcpy(&my_rlim, rlim, sizeof(struct rlimit));
	if (my_rlim.rlim_cur == 0) {
		my_rlim.rlim_cur = my_rlim.rlim_max;
	}

	return real_rlimit(resource, &my_rlim);
}
#endif
