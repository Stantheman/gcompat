#include <dlfcn.h>
#include <stddef.h>
#include <stdlib.h>

#define _frame_level(addr_buf, curr, frame, size)                              \
	do {                                                                   \
		if (__builtin_frame_address(frame) != NULL                     \
		    && (curr = __builtin_return_address(frame)) > 0x1000       \
		    && frame <= size) {                                        \
			addr_buf[frame] = curr;                                \
		} else {                                                       \
			return size;                                           \
		}                                                              \
	} while (0)

int backtrace(void **addr_buf, int size)
{
	void *curr;
	_frame_level(addr_buf, curr, 0, size);
	_frame_level(addr_buf, curr, 1, size);
	_frame_level(addr_buf, curr, 2, size);
	_frame_level(addr_buf, curr, 3, size);
	_frame_level(addr_buf, curr, 4, size);
	_frame_level(addr_buf, curr, 5, size);
	_frame_level(addr_buf, curr, 6, size);
	_frame_level(addr_buf, curr, 7, size);
	_frame_level(addr_buf, curr, 8, size);
	_frame_level(addr_buf, curr, 9, size);
	return 9;
}

char **backtrace_symbols(void *const *addr_buf, int size)
{
	char **result = calloc(sizeof(char *), size);
	if (result == NULL) {
		return result;
	}

	for (int next = 0; next < size; next++) {
		Dl_info info;
		int err = dladdr(addr_buf[next], &info);

		if (err != 0) {
			result[next] = "??:0";
		} else {
			result[next] = info.dli_sname;
		}
	}

	return result;
}
