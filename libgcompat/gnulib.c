#include <sys/select.h>
#include "internal.h"

#define REASON_FD_SET_OVERFLOW                                                 \
	"Fault: Overflow in fd_set detected.\n"                                \
	"Description: This is caused by a programmer naively attempting to\n"  \
	"  redefine FD_SETSIZE, which is not allowed on POSIX platforms.\n"    \
	"  The program must either be rebuilt with the correct FD_SETSIZE\n"   \
	"  definition, or else be rewritten to avoid use of select(2) in \n"   \
	"  general.  See also: poll(2).\n"                                     \
	"  libgcompat believes FD_SETSIZE to be %zu.\n"

unsigned long __fdelt_chk(unsigned long size)
{
	GCOMPAT__assert_with_reason(size < FD_SETSIZE, REASON_FD_SET_OVERFLOW,
	                            FD_SETSIZE);
	return size / (sizeof(unsigned long) << 3);
}
