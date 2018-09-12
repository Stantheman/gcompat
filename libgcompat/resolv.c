/*
 * Original author: Khem Raj <raj.khem@gmail.com>
 *
 * Mimick GLIBC's res_ninit() and res_nclose() for musl libc
 * Note: res_init() is actually deprecated according to
 * http://docs.oracle.com/cd/E36784_01/html/E36875/res-nclose-3resolv.html
 */

#include <resolv.h> /* res_state */
#include <stddef.h> /* NULL */
#include <string.h> /* memcpy, memset */

#include "alias.h" /* weak_alias */

int __res_ninit(res_state statp)
{
	int rc;

	if (statp == NULL) {
		return -1;
	}
	rc = res_init();
	if (statp != &_res) {
		memcpy(statp, &_res, sizeof(*statp));
	}

	return rc;
}
weak_alias(__res_ninit, res_ninit);

int __res_nclose(res_state statp)
{
	if (statp == NULL) {
		return -1;
	}
	if (statp != &_res) {
		memset(statp, 0, sizeof(*statp));
	}

	return 0;
}
weak_alias(__res_nclose, res_nclose);

int __res_search(const char *dname, int class, int type, unsigned char *answer,
                 int anslen)
{
	return res_search(dname, class, type, answer, anslen);
}
