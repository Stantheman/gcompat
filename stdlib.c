#include <assert.h>	// assert
#include <stdlib.h>	// strtod

char *__realpath_chk(const char *path, char *resolved_path)
{
	assert(path != NULL);
	return realpath(path, resolved_path);
}

double __strtod_internal(const char *__nptr, char **__endptr, int __group)
{
	assert(__group == 0);
	return strtod(__nptr, __endptr);
}
