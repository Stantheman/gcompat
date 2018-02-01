#include <assert.h>     /* assert */
#include <stddef.h>     /* NULL */
#include <sys/socket.h> /* recv, recvfrom */

/**
 * Receive a message from a connected socket, with buffer overflow checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---recv-chk-1.html
 */
ssize_t __recv_chk(int fd, void *buf, size_t len, size_t buflen, int flags)
{
	assert(buf != NULL);
	assert(buflen >= len);

	return recv(fd, buf, len, flags);
}

/**
 * Receive a message from a socket, with buffer overflow checking.
 *
 * LSB 5.0: LSB-Core-generic/baselib---recvfrom-chk-1.html
 */
ssize_t __recvfrom_chk(int fd, void *buf, size_t len, size_t buflen, int flags,
                       struct sockaddr *address, socklen_t *address_len)
{
	assert(buf != NULL);
	assert(buflen >= len);
	assert(address != NULL ? address_len != NULL : address_len == NULL);

	return recvfrom(fd, buf, len, flags, address, address_len);
}
