#include <math.h>	// isinf, isnan

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
