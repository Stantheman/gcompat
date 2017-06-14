#include <pthread.h>

int __register_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void)) {
	return pthread_atfork(prepare, parent, child);
}

int register_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void)) __attribute__ ((weak, alias("__register_atfork")));
