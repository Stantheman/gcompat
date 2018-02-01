#include <pthread.h>

#include "alias.h" /* weak_alias */

/**
 * Underlying function for pthread_cleanup_push.
 */
void __pthread_register_cancel(void *buf)
{
}

/**
 * Underlying function for pthread_cleanup_push.
 */
void __pthread_unregister_cancel(void *buf)
{
}

/**
 * Register fork handlers.
 *
 * LSB 5.0: LSB-Core-generic/baselib---register-atfork.html
 */
int __register_atfork(void (*prepare)(void), void (*parent)(void),
                      void (*child)(void), void *__dso_handle)
{
	return pthread_atfork(prepare, parent, child);
}
weak_alias(__register_atfork, register_atfork);
