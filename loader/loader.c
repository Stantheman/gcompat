/*
 * Copyright (c) 2017 William Pitcock <nenolod@dereferenced.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * This software is provided 'as is' and without any warranty, express or
 * implied.  In no event shall the authors be liable for any damages arising
 * from the use of this software.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#ifndef PATH_MAX
#define PATH_MAX      16384
#endif

#ifndef LINKER
#error LINKER must be defined
#endif

#ifndef LIBGCOMPAT
#error LIBGCOMPAT must be defined
#endif

int main(int argc, char *argv[], char *envp[]) {
	size_t i = 0;
	char target[PATH_MAX];
	char **new_argv = calloc(sizeof(char *), argc + 5);

	memset(target, 0, sizeof(target));
	if (readlink("/proc/self/exe", target, sizeof(target)) < 0) {
		perror("readlink");
		return EXIT_FAILURE;
	}

	new_argv[0] = argv[0];
	new_argv[1] = "--preload";
	new_argv[2] = LIBGCOMPAT;
	new_argv[3] = target;

	for (i = 1; i < argc; i++) {
		new_argv[3 + i] = argv[i];
	}

	execve(LINKER, new_argv, envp);

	/* execve only returns if there is an error. */
	perror("execve");
	return EXIT_FAILURE;
}
