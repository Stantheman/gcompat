/* Original author: Khem Raj <raj.khem@gmail.com> */
/***************************************************************************
 * resolv_compat.h
 *
 * Mimick GLIBC's res_ninit() and res_nclose() for musl libc
 * Note: res_init() is actually deprecated according to
 * http://docs.oracle.com/cd/E36784_01/html/E36875/res-nclose-3resolv.html
 **************************************************************************/
#include <resolv.h> /* res_state */
#include <string.h> /* memcpy, memset */

#include "alias.h" /* weak_alias */

static inline int __res_ninit(res_state statp)
{
	int rc = res_init();
	if (statp != &_res) {
		memcpy(statp, &_res, sizeof(*statp));
	}
	return rc;
}
weak_alias(__res_ninit, res_ninit);

static inline int __res_nclose(res_state statp)
{
	if (!statp) {
		return -1;
	}
	if (statp != &_res) {
		memset(statp, 0, sizeof(*statp));
	}
	return 0;
}
weak_alias(__res_nclose, res_nclose);
