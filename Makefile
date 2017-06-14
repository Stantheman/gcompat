LIBGCOMPAT_SRC = \
	libgcompat/backtrace.c		\
	libgcompat/dlmopen.c		\
	libgcompat/dlvsym.c		\
	libgcompat/gnulib.c		\
	libgcompat/malloc.c		\
	libgcompat/math.c		\
	libgcompat/resource.c		\
	libgcompat/setjmp.c		\
	libgcompat/stdio.c		\
	libgcompat/stdlib.c		\
	libgcompat/string.c		\
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
	gcc -o ${LIBGCOMPAT_NAME} -Wl,-soname,${LIBGCOMPAT_NAME} -shared ${LIBGCOMPAT_OBJ}

${LOADER_NAME}: ${LOADER_OBJ}
	gcc -o ${LOADER_NAME} -fPIE -static ${LOADER_OBJ}

.c.o:
	gcc -fPIC -DPIC -DLINKER=\"${LINKER_PATH}\" -DLIBGCOMPAT=\"${LIBGCOMPAT_PATH}\" ${CFLAGS} ${CPPFLAGS} -c -o $@ $<

clean:
	rm -f libgcompat/*.o loader/*.o ${LIBGCOMPAT_NAME} ${LOADER_NAME}

install: all
	install -D -m755 ${LIBGCOMPAT_NAME} ${DESTDIR}/${LIBGCOMPAT_PATH}
	install -D -m755 ${LOADER_NAME} ${DESTDIR}/${LOADER_PATH}
