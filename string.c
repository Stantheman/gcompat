#include <string.h>	/* strndup */

/* Literally a useless __ alias. */
char *__strndup(const char *str, size_t count)
{
	return strndup(str, count);
}

/* The existance of this method, and the fact it is used in real code, gives
 * me nightmares. */
void *rawmemchr(const void *s, int c)
{
	const unsigned char *haystack = s;
	unsigned char needle = (unsigned char)c;
	while(*haystack++ != needle);
	return (void *)haystack;
}

extern __typeof(rawmemchr) __rawmemchr __attribute__((weak, alias("rawmemchr")));

/* Another useless __ alias */
char *__strtok_r(char *str, const char *delim, char **saveptr)
{
	return strtok_r(str, delim, saveptr);
}

/* The "global" definition of strsep in glibc, used when architecture dependent
 * assembler versions aren't good enough. */
char *__strsep_g(char **stringp, const char *delim)
{
	return strsep(stringp, delim);
}
