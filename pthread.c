#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* "Now we are all sons of bitches." */
int pthread_setname_np(pthread_t thread, const char *name)
{
	char path[PATH_MAX];
	int fd;
	/* Cthulhu have mercy */
	pid_t *my_pid = (pid_t *)((void *)thread + (sizeof(uintptr_t) * 7));
	size_t len = strlen(name);

	if(len > 15)
	{
		return -ERANGE;
	}

	snprintf(path, PATH_MAX, "/proc/self/tid/%u/name", *my_pid);
	fd = open(path, O_RDWR);
	write(fd, name, len + 1);
	close(fd);

	return 0;
}
