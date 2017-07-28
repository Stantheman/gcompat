/* some musl versions incorrectly mark fgetpwent() as a GNU extension */
#define _GNU_SOURCE

#include <stdio.h>
#include <errno.h>
#include <pwd.h>
#include <string.h>


int getpwent_r(struct passwd *pwbuf, char *buf, size_t buflen, struct passwd **pwbufp) {
	struct passwd *pwd;

	if (pwbufp == NULL || pwbuf == NULL)
		return ERANGE;

	if (buflen < 1)
		return ERANGE;

	if (buf != NULL)
		*buf = '\0';

	if ((pwd = getpwent()) == NULL) {
		*pwbufp = NULL;
		return ENOENT;
	}

	memcpy(pwbuf, pwd, sizeof(*pwd));
	*pwbufp = pwbuf;

	return 0;
}


int fgetpwent_r(FILE *filp, struct passwd *pwbuf, char *buf, size_t buflen, struct passwd **pwbufp) {
	struct passwd *pwd;

	if (pwbufp == NULL || pwbuf == NULL)
		return ERANGE;

	if (buflen < 1)
		return ERANGE;

	if (buf != NULL)
		*buf = '\0';

	if ((pwd = fgetpwent(filp)) == NULL) {
		*pwbufp = NULL;
		return ENOENT;
	}

	memcpy(pwbuf, pwd, sizeof(*pwd));
	*pwbufp = pwbuf;

	return 0;
}
