#include <math.h> /* isfinite, isinf, isnan */

#include "alias.h" /* weak_alias */

/**
 * Test for finite value.
 */
int __finite(double arg)
{
	return isfinite(arg);
}
weak_alias(__finite, finite);

/**
 * Test for finite value.
 */
int __finitef(float arg)
{
	return isfinite(arg);
}
weak_alias(__finitef, finitef);

/**
 * Test for finite value.
 */
int __finitel(long double arg)
{
	return isfinite(arg);
}
weak_alias(__finitel, finitel);

/**
 * Test for infinity.
 *
 * LSB 5.0: LSB-Core-generic/baselib---isinf.html
 */
int __isinf(double arg)
{
	return isinf(arg);
}
weak_alias(__isinf, isinf);

/**
 * Test for infinity.
 *
 * LSB 5.0: LSB-Core-generic/baselib---isinff.html
 */
int __isinff(float arg)
{
	return isinf(arg);
}
weak_alias(__isinff, isinff);

/**
 * Test for infinity.
 *
 * LSB 5.0: LSB-Core-generic/baselib---isinfl.html
 */
int __isinfl(long double arg)
{
	return isinf(arg);
}
weak_alias(__isinfl, isinfl);

/**
 * Test for a NaN.
 *
 * LSB 5.0: LSB-Core-generic/baselib---isnan.html
 */
int __isnan(double arg)
{
	return isnan(arg);
}
weak_alias(__isnan, isnan);

/**
 * Test for a NaN.
 *
 * LSB 5.0: LSB-Core-generic/baselib---isnanf.html
 */
int __isnanf(float arg)
{
	return isnan(arg);
}
weak_alias(__isnanf, isnanf);

/**
 * Test for a NaN.
 *
 * LSB 5.0: LSB-Core-generic/baselib---isnanl.html
 */
int __isnanl(long double arg)
{
	return isnan(arg);
}
weak_alias(__isnanl, isnanl);
