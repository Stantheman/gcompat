#define _GNU_SOURCE /* Extra maths functions */
#include <math.h>   /* Literally everything */

#include "alias.h"    /* weak_alias */
#include "internal.h" /* GCOMPAT__assert_with_reason */

/**
 * Multiplies the first argument x by FLT_RADIX (probably 2) to the power of y.
 */
long double scalbl(long double x, long double y)
{
	/*
	 * XXX strictly not correct but:
	 * 1) Good Enough(TM)
	 * 2) scalbl is deprecated anyway
	 * */
	return scalblnl(x, (long int) y);
}

/*
 * The below require support for ynl/jnl which doesn't exist in musl and isn't
 * implemented in gcompat yet
 */
#if 0
/**
 * Return Bessel functions of x of the first kind of order n.
 */
long double jnl(int n, long double x)
{
	/* TODO implement */
	return 0;
}

/**
 * Return Bessel functions of x of the first kind of order 0.
 */
long double j0l(long double n)
{
	return jnl(0, n);
}

/**
 * Return Bessel functions of x of the first kind of order 1.
 */
long double j1l(long double n)
{
	return jnl(1, n);
}

/**
 * Return Bessel functions of x of the second kind of order n.
 */
long double ynl(int n, long double x)
{
	/* TODO implement */
	return 0;
}

/**
 * Return Bessel functions of x of the second kind of order 0.
 */
long double y0l(long double n)
{
	return ynl(0, n);
}

/**
 * Return Bessel functions of x of the second kind of order 1.
 */
long double y1l(long double n)
{
	return ynl(1, n);
}
#endif

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


/*
 * Finite specialisations of functions used by glibc, that aren't supposed to
 * return infinity.
 */

#define _ASSERT_FINITE(finite_fn, res)						\
	GCOMPAT__assert_with_reason(finite_fn(res),			\
		"infinite value returned in a function that returns a "	\
		"finite result");

#define ASSERT_FINITEF(res) _ASSERT_FINITE(isinff, res)
#define ASSERT_FINITE(res) _ASSERT_FINITE(isinf, res)
#define ASSERT_FINITEL(res) _ASSERT_FINITE(isinfl, res)

/**
 * Returns the principal value of the arc cosine of x, expressed in radians.
 */
float __acosf_finite(float x)
{
	float res = acosf(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the principal value of the arc cosine of x, expressed in radians.
 */
double __acos_finite(double x)
{
	double res = acos(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the principal value of the arc cosine of x, expressed in radians.
 */
long double __acosl_finite(long double x)
{
	long double res = acosl(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the nonnegative area hyperbolic cosine of x.
 */
double __acosh_finite(double x)
{
	double res = acosh(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the nonnegative area hyperbolic cosine of x.
 */
float __acoshf_finite(float x)
{
	float res = acoshf(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the nonnegative area hyperbolic cosine of x.
 */
long double __acoshl_finite(long double x)
{
	long double res = acoshl(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the principal value of the arc sine of x, expressed in radians.
 */
float __asinf_finite(float x)
{
	float res = asinf(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the principal value of the arc sine of x, expressed in radians.
 */
double __asin_finite(double x)
{
	double res = asin(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the principal value of the arc sine of x, expressed in radians.
 */
long double __asinl_finite(long double x)
{
	long double res = asinl(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the principal value of the arc tangent of x/y, expressed in radians.
 */
float __atan2f_finite(float x, float y)
{
	float res = atan2f(x, y);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the principal value of the arc tangent of x/y, expressed in radians.
 */
double __atan2_finite(double x, double y)
{
	double res = atan2(x, y);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the principal value of the arc tangent of x/y, expressed in radians.
 */
long double __atan2l_finite(long double x, long double y)
{
	long double res = atan2l(x, y);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the area hyperbolic tangent of x.
 */
float __atanhf_finite(float x)
{
	float res = atanhf(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the area hyperbolic tangent of x.
 */
double __atanh_finite(double x)
{
	double res = atanh(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the area hyperbolic tangent of x.
 */
long double __atanhl_finite(long double x)
{
	long double res = atanhl(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the hyperbolic cosine of x.
 */
float __coshf_finite(float x)
{
	float res = coshf(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the hyperbolic cosine of x.
 */
double __cosh_finite(double x)
{
	double res = cosh(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the hyperbolic cosine of x.
 */
long double __coshl_finite(long double x)
{
	long double res = coshl(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Return the value of 10 raised to the power of x.
 */
float __exp10f_finite(float x)
{
	float res = exp10f(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Return the value of 10 raised to the power of x.
 */
double __exp10_finite(double x)
{
	double res = exp10(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Return the value of 10 raised to the power of x.
 */
long double __exp10l_finite(long double x)
{
	long double res = exp10l(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the base-2 exponential function of x, which is 2 raised to the power x
 */
float __exp2f_finite(float x)
{
	float res = exp2f(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the base-2 exponential function of x, which is 2 raised to the power x
 */
double __exp2_finite(double x)
{
	double res = exp2(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the base-2 exponential function of x, which is 2 raised to the power x
 */
long double __exp2l_finite(long double x)
{
	long double res = exp2l(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the base-e exponential function of x, which is e raised to the power x
 */
float __expf_finite(float x)
{
	float res = expf(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the base-e exponential function of x, which is e raised to the power x
 */
double __exp_finite(double x)
{
	double res = exp(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the base-e exponential function of x, which is e raised to the power x
 */
long double __expl_finite(long double x)
{
	long double res = expl(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the floating-point remainder of x/y (rounded towards zero)
 */
float __fmodf_finite(float x, float y)
{
	float res = fmodf(x, y);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the floating-point remainder of x/y (rounded towards zero)
 */
double __fmod_finite(double x, double y)
{
	double res = fmod(x, y);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the floating-point remainder of x/y (rounded towards zero)
 */
long double __fmodl_finite(long double x, long double y)
{
	long double res = fmodl(x, y);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Computes the square root of the sum of the squares of x and y, without undue
 * overflow or underflow at intermediate stages of the computation.
 */
float __hypotf_finite(float x, float y)
{
	float res = hypotf(x, y);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Computes the square root of the sum of the squares of x and y, without undue
 * overflow or underflow at intermediate stages of the computation.
 */
double __hypot_finite(double x, double y)
{
	double res = hypot(x, y);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Computes the square root of the sum of the squares of x and y, without undue
 * overflow or underflow at intermediate stages of the computation.
 */
long double __hypotl_finite(long double x, long double y)
{
	long double res = hypotl(x, y);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Return Bessel functions of x of the first kind of orders 0.
 */
float __j0f_finite(float x)
{
	float res = j0f(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Return Bessel functions of x of the first kind of orders 0.
 */
double __j0_finite(double x)
{
	double res = j0(x);

	ASSERT_FINITE(res);

	return res;
}

/* The below requires support for j0l, see above */
#if 0
/**
 * Return Bessel functions of x of the first kind of orders 0.
 */
long double __j0l_finite(long double x)
{
	long double res = j0l(x);

	ASSERT_FINITEL(res);

	return res;
}
#endif

/**
 * Return Bessel functions of x of the first kind of orders 1.
 */
float __j1f_finite(float x)
{
	float res = j1f(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Return Bessel functions of x of the first kind of orders 1.
 */
double __j1_finite(double x)
{
	double res = j1(x);

	ASSERT_FINITE(res);

	return res;
}

/* The below requires support for j1l, see above */
#if 0
/**
 * Return Bessel functions of x of the first kind of orders 1.
 */
long double __j1l_finite(long double x)
{
	long double res = j1l(x);

	ASSERT_FINITEL(res);

	return res;
}
#endif

/**
 * Return the Bessel function of x of the first kind of order n.
 */
float __jnf_finite(int n, float x)
{
	float res = jnf(n, x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Return the Bessel function of x of the first kind of order n.
 */
double __jn_finite(int n, double x)
{
	double res = jn(n, x);

	ASSERT_FINITE(res);

	return res;
}

/* The below requires support for jnl, see above */
#if 0
/**
 * Return the Bessel function of x of the first kind of order n.
 */
long double __jnl_finite(int n, long double x)
{
	long double res = jnl(n, x);

	ASSERT_FINITEL(res);

	return res;
}
#endif

/**
 * Returns the natural logarithm of the absolute value of the Gamma function.
 */
float __lgammaf_finite(float x)
{
	float res = lgammaf(x);

	ASSERT_FINITEF(res);

	return res;
}
alias(__lgammaf_finite, __gammaf_finite);

/**
 * Returns the natural logarithm of the absolute value of the Gamma function.
 */
double __lgamma_finite(double x)
{
	double res = lgamma(x);

	ASSERT_FINITE(res);

	return res;
}
alias(__lgamma_finite, __gamma_finite);

/**
 * Returns the natural logarithm of the absolute value of the Gamma function.
 */
long double __lgammal_finite(long double x)
{
	long double res = lgammal(x);

	ASSERT_FINITEL(res);

	return res;
}
alias(__lgammal_finite, __gammal_finite);

/**
 * Returns the natural logarithm of the absolute value of the Gamma function.
 */
float __lgammaf_r_finite(float x, int *p)
{
	float res = lgammaf_r(x, p);

	ASSERT_FINITEF(res);

	return res;
}
alias(__lgammaf_r_finite, __gammaf_r_finite);

/**
 * Returns the natural logarithm of the absolute value of the Gamma function.
 */
double __lgamma_r_finite(double x, int *p)
{
	double res = lgamma_r(x, p);

	ASSERT_FINITE(res);

	return res;
}
alias(__lgamma_r_finite, __gamma_r_finite);

/**
 * Returns the natural logarithm of the absolute value of the Gamma function.
 */
long double __lgammal_r_finite(long double x, int *p)
{
	long double res = lgammal_r(x, p);

	ASSERT_FINITEL(res);

	return res;
}
alias(__lgammal_r_finite, __gammal_r_finite);

/**
 * Returns the common (base-10) logarithm of x.
 */
float __log10f_finite(float x)
{
	float res = log10f(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the common (base-10) logarithm of x.
 */
double __log10_finite(double x)
{
	double res = log10(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the common (base-10) logarithm of x.
 */
long double __log10l_finite(long double x)
{
	long double res = log10l(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the binary (base-2) logarithm of x.
 */
float __log2f_finite(float x)
{
	float res = log2f(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the binary (base-2) logarithm of x.
 */
double __log2_finite(double x)
{
	double res = log2(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the binary (base-2) logarithm of x.
 */
long double __log2l_finite(long double x)
{
	long double res = log2l(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the natural logarithm of x.
 */
float __logf_finite(float x)
{
	float res = logf(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the natural logarithm of x.
 */
double __log_finite(double x)
{
	double res = log(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the natural logarithm of x.
 */
long double __logl_finite(long double x)
{
	long double res = logl(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns x raised to the y exponent.
 */
float __powf_finite(float x, float y)
{
	float res = powf(x, y);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns x raised to the y exponent.
 */
double __pow_finite(double x, double y)
{
	double res = pow(x, y);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns x raised to the y exponent.
 */
long double __powl_finite(long double x, long double y)
{
	long double res = powl(x, y);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the floating-point remainder of x/y (rounded to nearest).
 */
float __remainderf_finite(float x, float y)
{
	float res = remainderf(x, y);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the floating-point remainder of x/y (rounded to nearest).
 */
double __remainder_finite(double x, double y)
{
	double res = remainder(x, y);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the floating-point remainder of x/y (rounded to nearest).
 */
long double __remainderl_finite(long double x, long double y)
{
	long double res = remainderl(x, y);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Multiplies the first argument x by FLT_RADIX (probably 2) to the power of y.
 */
float __scalbf_finite(float x, float y)
{
	float res = scalbf(x, y);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Multiplies the first argument x by FLT_RADIX (probably 2) to the power of y.
 */
double __scalb_finite(double x, double y)
{
	double res = scalb(x, y);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Multiplies the first argument x by FLT_RADIX (probably 2) to the power of y.
 */
long double __scalbl_finite(long double x, long double y)
{
	long double res = scalbl(x, y);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the hyperbolic sine of x.
 */
float __sinhf_finite(float x)
{
	float res = sinhf(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the hyperbolic sine of x.
 */
double __sinh_finite(double x)
{
	double res = sinh(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the hyperbolic sine of x.
 */
long double __sinhl_finite(long double x)
{
	long double res = sinhl(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Returns the square root of x.
 */
float __sqrtf_finite(float x)
{
	float res = sqrtf(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Returns the square root of x.
 */
double __sqrt_finite(double x)
{
	double res = sqrt(x);

	ASSERT_FINITE(res);

	return res;
}

/**
 * Returns the square root of x.
 */
long double __sqrtl_finite(long double x)
{
	long double res = sqrtl(x);

	ASSERT_FINITEL(res);

	return res;
}

/**
 * Return Bessel functions of x of the second kind of order 0.
 */
float __y0f_finite(float x)
{
	float res = y0f(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Return Bessel functions of x of the second kind of order 0.
 */
double __y0_finite(double x)
{
	double res = y0(x);

	ASSERT_FINITE(res);

	return res;
}

/* The below requires support for y0l, see above */
#if 0
/**
 * Return Bessel functions of x of the second kind of order 0.
 */
long double __y0l_finite(long double x)
{
	long double res = y0l(x);

	ASSERT_FINITEL(res);

	return res;
}
#endif

/**
 * Return Bessel functions of x of the second kind of order 1.
 */
float __y1f_finite(float x)
{
	float res = y1f(x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Return Bessel functions of x of the second kind of order 1.
 */
double __y1_finite(double x)
{
	double res = y1(x);

	ASSERT_FINITE(res);

	return res;
}

/* The below requires support for y1l, see above */
#if 0
/**
 * Return Bessel functions of x of the second kind of order 1.
 */
long double __y1l_finite(long double x)
{
	long double res = y1l(x);

	ASSERT_FINITEL(res);

	return res;
}
#endif

/**
 * Return Bessel functions of x of the second kind of order n.
 */
float __ynf_finite(int n, float x)
{
	float res = ynf(n, x);

	ASSERT_FINITEF(res);

	return res;
}

/**
 * Return Bessel functions of x of the second kind of order n.
 */
double __yn_finite(int n, double x)
{
	double res = yn(n, x);

	ASSERT_FINITE(res);

	return res;
}

/* The below requires support for ynl, see above */
#if 0
/**
 * Return Bessel functions of x of the second kind of order n.
 */
long double __ynl_finite(int n, long double x)
{
	long double res = ynl(n, x);

	ASSERT_FINITEL(res);

	return res;
}
#endif
