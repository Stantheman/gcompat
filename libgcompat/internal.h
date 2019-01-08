#ifndef LIBGCOMPAT_INTERNAL_H
#define LIBGCOMPAT_INTERNAL_H

void GCOMPAT__panic(const char *fmt, ...) __attribute__((noreturn));

#define GCOMPAT__assert_with_reason(chk, ...)                                  \
	do {                                                                   \
		if (!(chk)) {                                                  \
			GCOMPAT__panic(__VA_ARGS__);                           \
		}                                                              \
	} while (0);

#endif
