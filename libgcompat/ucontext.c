#include <errno.h> /* errno, ENOSYS */

#ifndef HAVE_LIBUCONTEXT

int getcontext(void *ucp)
{
	errno = ENOSYS;
	return -1;
}

#endif
