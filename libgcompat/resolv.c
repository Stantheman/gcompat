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

static inline int res_ninit(res_state statp)
{
	int rc = res_init();
	if (statp != &_res) {
		memcpy(statp, &_res, sizeof(*statp));
	}
	return rc;
}

static inline int res_nclose(res_state statp)
{
	if (!statp) {
		return -1;
	}
	if (statp != &_res) {
		memset(statp, 0, sizeof(*statp));
	}
	return 0;
}

extern __typeof(res_ninit) __res_ninit
    __attribute__((weak, alias("res_ninit")));
extern __typeof(res_nclose) __res_nclose
    __attribute__((weak, alias("res_nclose")));
