#include <sys/select.h>
#include "internal.h"

#define REASON_FD_SET_OVERFLOW										\
	"Fault: Overflow in fd_set detected.\n"								\
	"Description: This is caused by a programmer naively attempting to redefine FD_SETSIZE,\n"	\
	"  which is not allowed on POSIX platforms.  The program must be either rebuilt\n"		\
	"  with the correct FD_SETSIZE definition, or preferably rewritten to avoid use\n"		\
	"  of select(2) in general.  See also: poll(2).\n"						\
	"  libgcompat believes FD_SETSIZE to be %zu.\n"

unsigned long __fdelt_chk(unsigned long size)
{
	GCOMPAT__assert_with_reason(size < FD_SETSIZE, REASON_FD_SET_OVERFLOW, FD_SETSIZE);
	return size / (sizeof(unsigned long) << 3);
}
