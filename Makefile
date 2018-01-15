LIBGCOMPAT_INCLUDE = \
	libgcompat/alias.h
LIBGCOMPAT_SRC = \
	libgcompat/dlfcn.c		\
	libgcompat/execinfo.c		\
	libgcompat/gnulib.c		\
	libgcompat/malloc.c		\
	libgcompat/math.c		\
	libgcompat/pthread.c		\
	libgcompat/pwd.c		\
	libgcompat/resolv.c		\
	libgcompat/resource.c		\
	libgcompat/setjmp.c		\
	libgcompat/stdio.c		\
	libgcompat/stdlib.c		\
	libgcompat/string.c		\
	libgcompat/sysctl.c		\
	libgcompat/ucontext.c		\
	libgcompat/version.c
LIBGCOMPAT_OBJ = ${LIBGCOMPAT_SRC:.c=.o}
LIBGCOMPAT_SOVERSION = 0
LIBGCOMPAT_NAME = libgcompat.so.${LIBGCOMPAT_SOVERSION}
LIBGCOMPAT_PATH = /lib/${LIBGCOMPAT_NAME}

LOADER_SRC = \
	loader/loader.c
LOADER_OBJ = ${LOADER_SRC:.c=.o}
LOADER_NAME = ld-linux.so.2
LOADER_PATH = /lib/${LOADER_NAME}

all: ${LIBGCOMPAT_NAME} ${LOADER_NAME}

${LIBGCOMPAT_NAME}: ${LIBGCOMPAT_OBJ}
	$(CC) -o ${LIBGCOMPAT_NAME} -Wl,-soname,${LIBGCOMPAT_NAME} \
		-shared ${LIBGCOMPAT_OBJ}

${LIBGCOMPAT_OBJ}: ${LIBGCOMPAT_INCLUDE}

${LOADER_NAME}: ${LOADER_OBJ}
	$(CC) -o ${LOADER_NAME} -fPIE -static ${LOADER_OBJ}

.c.o:
	$(CC) -c -D_BSD_SOURCE -DLIBGCOMPAT=\"${LIBGCOMPAT_PATH}\" \
		-DLINKER=\"${LINKER_PATH}\" -DLOADER=\"${LOADER_NAME}\" \
		-fPIC -std=c99 -Wall -Wextra -Wno-frame-address \
		-Wno-unused-parameter ${CFLAGS} ${CPPFLAGS} -o $@ $<

clean:
	rm -f libgcompat/*.o loader/*.o ${LIBGCOMPAT_NAME} ${LOADER_NAME}

format:
	clang-format -i ${LIBGCOMPAT_SRC} ${LOADER_SRC}

install: all
	install -D -m755 ${LIBGCOMPAT_NAME} ${DESTDIR}/${LIBGCOMPAT_PATH}
	install -D -m755 ${LOADER_NAME} ${DESTDIR}/${LOADER_PATH}

.PHONY: all clean format install
