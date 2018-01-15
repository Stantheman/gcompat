#include <dlfcn.h>
#include <fcntl.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef LINKER
#error LINKER must be defined
#endif

static char exe[PATH_MAX], *linker;
static ssize_t (*real_readlink)(const char *, char *, size_t);

ssize_t readlink(const char *path, char *buf, size_t len)
{
	if (real_readlink == NULL) {
		real_readlink = dlsym(RTLD_NEXT, "readlink");
		if (real_readlink == NULL) {
			return -1;
		}
	}

	if (!strcmp(path, "/proc/self/exe")) {
		int fd;

		if (exe[0] == '\0') {
			if (linker == NULL) {
				linker = realpath(LINKER, NULL);
				if (linker == NULL) {
					return -1;
				}
			}
			if (real_readlink(path, exe, sizeof(exe)) < 1) {
				goto fail;
			}
			if (!strcmp(exe, linker)) {
				char c;
				int arg = 0;
				ssize_t arglen;

				fd = open("/proc/self/cmdline",
				          O_RDONLY | O_CLOEXEC);
				if (fd < 0) {
					goto fail;
				}
				/* Skip the --argv0/--preload ldso args.
				 * This number must be kept in sync with the
				 * argument order in loader/loader.c */
				while (arg < 5) {
					if (read(fd, &c, 1) != 1) {
						goto fail_close;
					}
					if (c == '\0') {
						++arg;
					}
				}
				/* Read the executable path from the cmdline. */
				arglen = read(fd, exe, sizeof(exe));
				if (arglen < 1) {
					goto fail_close;
				}
				close(fd);
				/* Ensure the path exists, fits, and has NUL. */
				if (exe[0] == '\0') {
					goto fail;
				}
				if (strnlen(exe, arglen) == (size_t) arglen) {
					goto fail;
				}
			}
		}

		return stpncpy(buf, exe, len) - buf;

	fail_close:
		close(fd);
	fail:
		exe[0] = '\0';
		return -1;
	}

	return real_readlink(path, buf, len);
}
