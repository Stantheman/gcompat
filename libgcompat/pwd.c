/* some musl versions incorrectly mark fgetpwent() as a GNU extension */
#define _GNU_SOURCE
#include <assert.h>  /* assert */
#include <errno.h>   /* ENOENT, ERANGE */
#include <pthread.h> /* pthread_mutex_* */
#include <pwd.h>     /* fgetpwent, getpwent, struct passwd */
#include <stddef.h>  /* NULL, size_t */
#include <stdio.h>   /* FILE */
#include <string.h>  /* memcpy, stpcpy, strlcpy, strlen */

static pthread_mutex_t pwent_mutex = PTHREAD_MUTEX_INITIALIZER;

static int __fgetpwent_r(FILE *stream, struct passwd *pwd, char *buf,
                         size_t len, struct passwd **result)
{
	struct passwd *pwtmp;
	char *cursor = buf, *end = buf + len;

	*result = NULL;
	pthread_mutex_lock(&pwent_mutex);
	pwtmp = stream != NULL ? fgetpwent(stream) : getpwent();
	if (pwtmp == NULL) {
		pthread_mutex_unlock(&pwent_mutex);
		return ENOENT;
	}
	memcpy(pwd, pwtmp, sizeof(*pwd));
	if (pwtmp->pw_name != NULL) {
		pwd->pw_name = cursor;
		cursor += strlcpy(cursor, pwtmp->pw_name, end - cursor) + 1;
		if (cursor > end) {
			goto err_unlock;
		}
	}
	if (pwtmp->pw_passwd != NULL) {
		pwd->pw_passwd = cursor;
		cursor += strlcpy(cursor, pwtmp->pw_passwd, end - cursor) + 1;
		if (cursor > end) {
			goto err_unlock;
		}
	}
	if (pwtmp->pw_gecos != NULL) {
		pwd->pw_gecos = cursor;
		cursor += strlcpy(cursor, pwtmp->pw_gecos, end - cursor) + 1;
		if (cursor > end) {
			goto err_unlock;
		}
	}
	if (pwtmp->pw_dir != NULL) {
		pwd->pw_dir = cursor;
		cursor += strlcpy(cursor, pwtmp->pw_dir, end - cursor) + 1;
		if (cursor > end) {
			goto err_unlock;
		}
	}
	if (pwtmp->pw_shell != NULL) {
		pwd->pw_shell = cursor;
		cursor += strlcpy(cursor, pwtmp->pw_shell, end - cursor) + 1;
		if (cursor > end) {
			goto err_unlock;
		}
	}
	pthread_mutex_unlock(&pwent_mutex);
	*result = pwd;

	return 0;

err_unlock:
	pthread_mutex_unlock(&pwent_mutex);
	return ERANGE;
}

/**
 * Get passwd file entry.
 */
int fgetpwent_r(FILE *stream, struct passwd *pwd, char *buf, size_t len,
                struct passwd **result)
{
	assert(stream != NULL);

	return fgetpwent_r(stream, pwd, buf, len, result);
}

/**
 * Get user database entry.
 *
 * LSB 5.0: LSB-Core-generic/baselib-getpwent-r-1.html
 */
int getpwent_r(struct passwd *pwd, char *buf, size_t len,
               struct passwd **result)
{
	return __fgetpwent_r(NULL, pwd, buf, len, result);
}
