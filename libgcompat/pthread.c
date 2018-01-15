#include <pthread.h>

#include "alias.h" /* weak_alias */

int __register_atfork(void (*prepare)(void), void (*parent)(void),
                      void (*child)(void))
{
	return pthread_atfork(prepare, parent, child);
}
weak_alias(__register_atfork, register_atfork);

void __pthread_register_cancel(void *buf)
{
}

void __pthread_unregister_cancel(void *buf)
{
}
