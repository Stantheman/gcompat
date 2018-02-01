/* some musl versions incorrectly mark fgetgrent() as a GNU extension */
#define _GNU_SOURCE
#include <assert.h>  /* assert */
#include <errno.h>   /* ENOENT, ERANGE */
#include <grp.h>     /* fgetgrent, getgrent, struct group */
#include <pthread.h> /* pthread_mutex_* */
#include <stddef.h>  /* NULL, size_t */
#include <stdint.h>  /* ptrdiff_t, uintptr_t */
#include <stdio.h>   /* FILE */
#include <string.h>  /* memcpy, stpcpy, strlcpy, strlen */

#define ALIGN_PTR_TO_SIZE_OF(ptr, type)                                        \
	((type *) ((((uintptr_t)(ptr)) + sizeof(type) - 1)                     \
	           & ~(sizeof(type) - 1)))

static pthread_mutex_t grent_mutex = PTHREAD_MUTEX_INITIALIZER;

static int __fgetgrent_r(FILE *stream, struct group *grp, char *buf, size_t len,
                         struct group **result)
{
	struct group *grtmp;
	char *cursor = buf, *end = buf + len;

	*result = NULL;
	pthread_mutex_lock(&grent_mutex);
	grtmp = stream != NULL ? fgetgrent(stream) : getgrent();
	if (grtmp == NULL) {
		pthread_mutex_unlock(&grent_mutex);
		return ENOENT;
	}
	memcpy(grp, grtmp, sizeof(*grp));
	if (grtmp->gr_name != NULL) {
		grp->gr_name = cursor;
		cursor += strlcpy(cursor, grtmp->gr_name, end - cursor) + 1;
		if (cursor > end) {
			goto err_unlock;
		}
	}
	if (grtmp->gr_passwd != NULL) {
		grp->gr_passwd = cursor;
		cursor += strlcpy(cursor, grtmp->gr_passwd, end - cursor) + 1;
		if (cursor > end) {
			goto err_unlock;
		}
	}
	if (grtmp->gr_mem != NULL) {
		char **members = ALIGN_PTR_TO_SIZE_OF(cursor, char *);
		ptrdiff_t nameslen = 0;
		size_t nmem = 0;

		/* Calculate total size of strings plus their pointers. */
		while (grtmp->gr_mem[nmem++] != NULL) {
			nameslen += strlen(grtmp->gr_mem[nmem - 1]) + 1;
		}
		nameslen += nmem * sizeof(*members);
		if (nameslen > end - ((char *) members)) {
			goto err_unlock;
		}
		/* Copy the pointers, including the NULL sentinel. */
		for (size_t i = 0; i < nmem; ++i) {
			members[i] = grtmp->gr_mem[i];
		}
		/* Copy the strings (the NULL sentinel doesn't point to one). */
		cursor = (char *) &members[nmem];
		for (size_t i = 0; i < nmem - 1; ++i) {
			cursor = stpcpy(cursor, members[i]) + 1;
		}
	}
	pthread_mutex_unlock(&grent_mutex);
	*result = grp;

	return 0;

err_unlock:
	pthread_mutex_unlock(&grent_mutex);
	return ERANGE;
}

/**
 * Get group file entry.
 */
int fgetgrent_r(FILE *stream, struct group *grp, char *buf, size_t len,
                struct group **result)
{
	assert(stream != NULL);

	return __fgetgrent_r(stream, grp, buf, len, result);
}

/**
 * Get group database entry.
 *
 * LSB 5.0: LSB-Core-generic/baselib-getgrent-r-1.html
 */
int getgrent_r(struct group *grp, char *buf, size_t len, struct group **result)
{
	return __fgetgrent_r(NULL, grp, buf, len, result);
}
