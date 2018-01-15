#include <assert.h> /* assert */
#include <stdarg.h> /* va_list, va_start, va_end */
#include <stddef.h> /* NULL */
#include <syslog.h> /* vsyslog */

void __vsyslog_chk(int priority, int flag, const char *format, va_list ap);

/**
 * Log a message, with stack checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---syslog-chk-1.html
 */
void __syslog_chk(int priority, int flag, const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	__vsyslog_chk(priority, flag, format, ap);
	va_end(ap);
}

/**
 * Log a message, with stack checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---vsyslog-chk-1.html
 */
void __vsyslog_chk(int priority, int flag, const char *format, va_list ap)
{
	assert(format != NULL);

	vsyslog(priority, format, ap);
}
