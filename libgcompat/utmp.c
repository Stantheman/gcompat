#include <stddef.h> /* NULL */
#include <utmpx.h>   /* struct utmp */

/**
 * Get user accounting database entries.
 *
 * LSB 5.0: LSB-Core-generic/baselib-getutent-r-3.html
 */
int getutent_r(struct utmp *buffer, struct utmp **result)
{
	/* musl does not implement getutent(). */
	*result = NULL;
	return -1;
}
