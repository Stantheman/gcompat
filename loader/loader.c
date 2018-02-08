/*
 * Copyright (c) 2017 William Pitcock <nenolod@dereferenced.org>
 * Copyright (c) 2018 Samuel Holland <samuel@sholland.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * This software is provided 'as is' and without any warranty, express or
 * implied.  In no event shall the authors be liable for any damages arising
 * from the use of this software.
 */

#include <limits.h> /* PATH_MAX */
#include <stddef.h> /* NULL */
#include <stdio.h>  /* fputs, fwrite, stderr */
#include <stdlib.h> /* calloc, EXIT_FAILURE, getenv */
#include <string.h> /* strcpy, strlcpy */
#include <unistd.h> /* execve, ssize_t */

#ifndef PATH_MAX
#define PATH_MAX 16384
#endif

#ifndef LIBGCOMPAT
#error LIBGCOMPAT must be defined
#endif

#ifndef LINKER
#error LINKER must be defined
#endif

#ifndef LOADER
#error LOADER must be defined
#endif

void usage(void)
{
	printf("This is the gcompat ELF interpreter stub.\n");
	printf("You are not meant to run this directly.\n");
}

/*
 * Given the argv { "foo", "bar", "baz" }, and the environment variable
 * "LD_PRELOAD=/another/preload.so", the new argv will be {
 *         "ld-linux-$ARCH.so.N",
 *         "--argv0",
 *         "foo",
 *         "--preload",
 *         "/path/to/libgcompat.so /another/preload.so",
 *         "/path/to/foo",
 *         "bar",
 *         "baz"
 * }.
 *
 * NOTE: The new argv needs 6 more entries than the original argc: five for
 * arguments added at the beginning, and one for the NULL sentinel at the end
 * not included in argc. Because calloc() is used, the sentinel is not
 * explicitly set on its own, but *it is still there*!
 *
 * NOTE: The name given in argv[0] to musl *must* match glibc's ld.so filename.
 * Many glibc-linked programs have an explicit dependency on its ld.so, but the
 * file placed at that path (this loader) is not a real shared library. If musl
 * tries to load this file as a shared library, it will fail. Thankfully, since
 * musl treats argv[0] as "its" name when run directly, it considers a library
 * by that name to already be loaded, and ignores the problematic dependency.
 *
 * NOTE: LD_PRELOAD entries are processed in order, and the environment variable
 * is ignored if the parameter is given. In case the glibc-linked program needs
 * another preloaded library, it should be appended to the argument so it gets
 * loaded after libgcompat. Leave the environment variable as is, so if the
 * program runs other glibc-linked programs, the same transformation gets
 * applied there as well.
 *
 * NOTE: In order for the program to be able to re-exec itself it needs the
 * fully-resolved path from /proc/self/exe ("target" below). This path is given
 * to musl on the command line in new_argv[5], but it is not directly available
 * to the program. An intercepted readlink("/proc/self/exe") must read it from
 * /proc/self/cmdline. Thus, if its position in new_argv changes, that function
 * must also be updated to match.
 */
int main(int argc, char *argv[], char *envp[])
{
	char **new_argv = calloc(argc + 6, sizeof(char *));
	char preload[PATH_MAX];
	char target[PATH_MAX];
	ssize_t i, j, len;

	strcpy(preload, LIBGCOMPAT " ");
	if (getenv("LD_PRELOAD") != NULL) {
		len = strlcat(preload, getenv("LD_PRELOAD"), sizeof(preload));
		if ((size_t) len >= sizeof(preload)) {
			fputs("too many preloaded libraries", stderr);
			return EXIT_FAILURE;
		}
	}

	len = readlink("/proc/self/exe", target, sizeof(target));
	if (len < 0 || len == sizeof(target)) {
		perror("readlink");
		return EXIT_FAILURE;
	}
	target[len] = '\0';

	/* somebody is trying to run the loader directly */
	if (strstr(target, LOADER) != NULL) {
		usage();
		return EXIT_FAILURE;
	}

	new_argv[0] = LOADER;
	new_argv[1] = "--argv0";
	new_argv[2] = argv[0];
	new_argv[3] = "--preload";
	new_argv[4] = preload;
	new_argv[5] = target;
	for (i = 6, j = 1; j < argc; ++i, ++j) {
		new_argv[i] = argv[j];
	}

	execve(LINKER, new_argv, envp);

	/* execve only returns if there is an error. */
	perror("execve");
	return EXIT_FAILURE;
}
