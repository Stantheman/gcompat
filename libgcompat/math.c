#include <math.h> /* isinf, isnan */

int __isinff(float number)
{
	return isinf(number);
}

int __isinf(double number)
{
	return isinf(number);
}

int __isnanf(float number)
{
	return isnan(number);
}

int __isnan(double number)
{
	return isnan(number);
}

extern __typeof(__isnanf) isnanf __attribute__((weak, alias("__isnanf")));
extern __typeof(__isnan) isnan __attribute__((weak, alias("__isnan")));
extern __typeof(__isinff) isinff __attribute__((weak, alias("__isinff")));
extern __typeof(__isinf) isinf __attribute__((weak, alias("__isinf")));
