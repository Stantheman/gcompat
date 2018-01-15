#include <dlfcn.h>  /* dladdr */
#include <stddef.h> /* NULL */
#include <stdint.h> /* uintptr_t */
#include <stdlib.h> /* calloc */
#include <string.h> /* strlen */
#include <unistd.h> /* write */

#define get_frame_level(array, size, n)                                        \
	do {                                                                   \
		if (n >= size || __builtin_frame_address(n) == NULL) {         \
			return n;                                              \
		}                                                              \
		void *address = __builtin_return_address(n);                   \
		array[n] = __builtin_extract_return_addr(address);             \
		if ((uintptr_t) array[n] < 0x1000) {                           \
			return n;                                              \
		}                                                              \
	} while (0)

/**
 * Obtain a backtrace for the calling program.
 *
 * LSB 5.0: LSB-Core-generic/baselib-backtrace-1.html
 */
int backtrace(void **array, int size)
{
	get_frame_level(array, size, 0);
	get_frame_level(array, size, 1);
	get_frame_level(array, size, 2);
	get_frame_level(array, size, 3);
	get_frame_level(array, size, 4);
	get_frame_level(array, size, 5);
	get_frame_level(array, size, 6);
	get_frame_level(array, size, 7);
	get_frame_level(array, size, 8);
	get_frame_level(array, size, 9);
	return 10;
}

/**
 * Translate addresses into symbol information.
 *
 * LSB 5.0: LSB-Core-generic/baselib-backtrace-1.html
 */
const char **backtrace_symbols(void *const *array, int size)
{
	const char **result = calloc(size, sizeof(char *));

	if (result == NULL) {
		return NULL;
	}
	for (int i = 0; i < size; ++i) {
		Dl_info info;

		if (dladdr(array[i], &info) && info.dli_sname != NULL) {
			result[i] = info.dli_sname;
		} else {
			result[i] = "??:0";
		}
	}

	return result;
}

/**
 * Write symbol information to a file without allocating memory.
 *
 * LSB 5.0: LSB-Core-generic/baselib-backtrace-1.html
 */
void backtrace_symbols_fd(void *const *array, int size, int fd)
{
	for (int i = 0; i < size; ++i) {
		Dl_info info;
		const char *line;
		int len;

		if (dladdr(array[i], &info) && info.dli_sname != NULL) {
			line = info.dli_sname;
			len = strlen(line);
		} else {
			line = "??:0";
			len = sizeof("??:0") - 1;
		}
		while (len > 0) {
			int written = write(fd, line, len);

			if (written < 1) {
				return;
			}
			line += written;
			len -= written;
		}
		if (write(fd, "\n", 1) != 1) {
			return;
		}
	}
}
