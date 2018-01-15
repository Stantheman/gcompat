#include <math.h> /* isinf, isnan */

#include "alias.h" /* weak_alias */

int __isinff(float number)
{
	return isinf(number);
}
weak_alias(__isinff, isinff);

int __isinf(double number)
{
	return isinf(number);
}
weak_alias(__isinf, isinf);

int __isnanf(float number)
{
	return isnan(number);
}
weak_alias(__isnanf, isnanf);

int __isnan(double number)
{
	return isnan(number);
}
weak_alias(__isnan, isnan);
