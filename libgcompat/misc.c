#include <stdlib.h>        /* abort, at_quick_exit */
#include <sys/stat.h>      /* dev_t */
#include <sys/sysmacros.h> /* major, makedev, minor */

/**
 * Terminate a function in case of buffer overflow.
 *
 * LSB 5.0: LSB-Core-generic/baselib---chk-fail-1.html
 */
void __chk_fail(void)
{
	abort();
}

int __cxa_at_quick_exit(void (*func)(void), void *__dso_handle)
{
	return at_quick_exit(func);
}

unsigned int gnu_dev_major(dev_t dev)
{
	return major(dev);
}

dev_t gnu_dev_makedev(unsigned int maj, unsigned int min)
{
	return makedev(maj, min);
}

unsigned int gnu_dev_minor(dev_t dev)
{
	return minor(dev);
}
