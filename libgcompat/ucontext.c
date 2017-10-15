#include <errno.h>	/* errno, ENOSYS */

int getcontext(void *ucp)
{
	errno = ENOSYS;
	return -1;
}
