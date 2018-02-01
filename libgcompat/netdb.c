#include <errno.h>  /* ENOENT */
#include <netdb.h>  /* getproto* */
#include <stddef.h> /* NULL, size_t */
#include <string.h> /* memcpy */

/**
 * Retrieve information from the network protocol database by protocol name,
 * reentrantly.
 *
 * LSB 5.0: LSB-Core-generic/baselib-getprotobyname-r.html
 */
int getprotobyname_r(const char *name, struct protoent *result_buf, char *buf,
                     size_t buflen, struct protoent **result)
{
	struct protoent *prototmp = getprotobyname(name);

	/* musl does not reuse static storage, so no race is possible. */
	if (prototmp == NULL) {
		*result = NULL;
		return ENOENT;
	}
	*result = memcpy(result_buf, prototmp, sizeof(*result_buf));

	return 0;
}

/**
 * Retrieve information from the network protocol database by protocol number,
 * reentrantly.
 *
 * LSB 5.0: LSB-Core-generic/baselib-getprotobynumber-r.html
 */
int getprotobynumber_r(int proto, struct protoent *result_buf, char *buf,
                       size_t buflen, struct protoent **result)
{
	struct protoent *prototmp = getprotobynumber(proto);

	/* musl does not reuse static storage, so no race is possible. */
	if (prototmp == NULL) {
		*result = NULL;
		return ENOENT;
	}
	*result = memcpy(result_buf, prototmp, sizeof(*result_buf));

	return 0;
}

/**
 * Read the next entry of the protocol database, reentrantly.
 *
 * LSB 5.0: LSB-Core-generic/baselib-getprotoent-r.html
 */
int getprotoent_r(struct protoent *result_buf, char *buf, size_t buflen,
                  struct protoent **result)
{
	struct protoent *prototmp = getprotoent();

	/* musl does not reuse static storage, so no race is possible. */
	if (prototmp == NULL) {
		*result = NULL;
		return ENOENT;
	}
	*result = memcpy(result_buf, prototmp, sizeof(*result_buf));

	return 0;
}

/**
 * Read the next entry of the network services database, reentrantly.
 *
 * LSB 5.0: LSB-Core-generic/baselib-getservent-r.html
 */
int getservent_r(struct servent *result_buf, char *buf, size_t buflen,
                 struct servent **result)
{
	/* musl does not implement getservent(). */
	*result = NULL;
	return ENOENT;
}
