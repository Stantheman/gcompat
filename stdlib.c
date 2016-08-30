#include <assert.h>	// assert
#include <stdlib.h>	// strtod

double __strtod_internal(const char *__nptr, char **__endptr, int __group)
{
	assert(__group == 0);
	return strtod(__nptr, __endptr);
}
