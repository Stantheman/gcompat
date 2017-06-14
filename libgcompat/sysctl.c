#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>


struct __sysctl_args {
	int *name;
	int nlen;
	void *oldval;
	size_t *oldlenp;
	void *newval;
	size_t newlen;
};


int sysctl (int *name, int nlen, void *oldval, size_t *oldlenp, void *newval, size_t newlen) {
	struct __sysctl_args args = {
		.name = name,
		.nlen = nlen,
		.oldval = oldval,
		.oldlenp = oldlenp,
		.newval = newval,
		.newlen = newlen
	};

	return syscall(SYS__sysctl, &args);
}
