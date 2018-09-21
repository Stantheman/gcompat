#include <pthread.h> /* NULL, pthread_{key,once,{get,set}specific} */
#include <stdlib.h>  /* malloc, free */

#include "internal.h"

struct dtor_node {
	struct dtor_node *next;
	void (*func)(void *);
	void *obj;
};

static pthread_key_t key;
static pthread_once_t once = PTHREAD_ONCE_INIT;

static void run_dtors(void *head)
{
	struct dtor_node *next, *node = head;

	while (node != NULL) {
		next = node->next;
		node->func(node->obj);
		free(node);
		node = next;
	}
}

static void create_key(void)
{
	int res = pthread_key_create(&key, run_dtors);

	GCOMPAT__assert_with_reason(res, "No key for thread_atexit list");
}

/**
 * Register a destructor to run at thread exit.
 *
 * See
 * https://sourceware.org/glibc/wiki/Destructor%20support%20for%20thread_local%20variables
 */
int __cxa_thread_atexit_impl(void (*func)(void *), void *obj, void *dso_symbol)
{
	struct dtor_node *node;

	pthread_once(&once, create_key);

	node = malloc(sizeof(*node));
	GCOMPAT__assert_with_reason(node, "No memory for thread_atexit node");
	node->next = pthread_getspecific(key);
	node->func = func;
	node->obj = obj;

	int res = pthread_setspecific(key, node);
	GCOMPAT__assert_with_reason(!res, "Cannot update thread_atexit list");

	return 0;
}
