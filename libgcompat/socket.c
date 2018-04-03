#include <assert.h>     /* assert */
#include <stddef.h>     /* NULL */
#include <poll.h>	/* poll, pollfd, nfds_t */
#include <sys/socket.h> /* recv, recvfrom */

/**
 * Found in the wild needed by libcef.  It looks like glibc moved to a
 * pure preprocessor-based solution some time ago, but this remains for
 * compatibility.
 */
struct cmsghdr *__cmsg_nxthdr(struct msghdr *msg, struct cmsghdr *cmsg)
{
	return CMSG_NXTHDR(msg, cmsg);
}

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

/**
 * Checked version of poll, not in LSB but found in the wild.
 *
 * This checks if the size of fds is large enough to hold all the fd's claimed
 * in nfds.
 */
int __poll_chk(struct pollfd *fds, nfds_t nfds, int timeout, size_t fdslen)
{
	assert((fdslen / sizeof(*fds)) < nfds);

	return poll(fds, nfds, timeout);
}
