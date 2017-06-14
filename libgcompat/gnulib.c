#include <assert.h>
#include <sys/select.h>

unsigned long __fdelt_chk(unsigned long size)
{
	assert(size < FD_SETSIZE);
	return size / (sizeof(unsigned long)<<3);
}
