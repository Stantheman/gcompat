LIBGCOMPAT_INCLUDE = \
	libgcompat/alias.h \
	libgcompat/internal.h
LIBGCOMPAT_SRC = \
	libgcompat/ctype.c		\
	libgcompat/cxx_thread.c		\
	libgcompat/dlfcn.c		\
	libgcompat/error.c		\
	libgcompat/execinfo.c		\
	libgcompat/gnulib.c		\
	libgcompat/grp.c		\
	libgcompat/internal.c		\
	libgcompat/malloc.c		\
	libgcompat/math.c		\
	libgcompat/misc.c		\
	libgcompat/netdb.c		\
	libgcompat/pthread.c		\
	libgcompat/pwd.c		\
	libgcompat/readlink.c		\
	libgcompat/realpath.c		\
	libgcompat/resolv.c		\
	libgcompat/resource.c		\
	libgcompat/setjmp.c		\
	libgcompat/signal.c		\
	libgcompat/socket.c		\
	libgcompat/stdio.c		\
	libgcompat/stdlib.c		\
	libgcompat/string.c		\
	libgcompat/sysctl.c		\
	libgcompat/syslog.c		\
	libgcompat/ucontext.c		\
	libgcompat/unistd.c		\
	libgcompat/utmp.c		\
	libgcompat/version.c		\
	libgcompat/wchar.c
LIBGCOMPAT_OBJ = ${LIBGCOMPAT_SRC:.c=.o}
LIBGCOMPAT_SOVERSION = 0
LIBGCOMPAT_NAME = libgcompat.so.${LIBGCOMPAT_SOVERSION}
LIBGCOMPAT_PATH = /lib/${LIBGCOMPAT_NAME}

LOADER_SRC = \
	loader/loader.c
LOADER_OBJ = ${LOADER_SRC:.c=.o}
LOADER_NAME = ld-linux.so.2
LOADER_PATH = /lib/${LOADER_NAME}

PKG_CONFIG ?= pkg-config

ifdef WITH_LIBUCONTEXT
LIBUCONTEXT_CFLAGS = -DWITH_LIBUCONTEXT
LIBUCONTEXT_LIBS   = -lucontext
endif

ifndef WITH_OBSTACK
WITH_OBSTACK = $(shell \
  for pkg in obstack obstack-standalone; do \
    ${PKG_CONFIG} --exists "$$pkg" && { echo "$$pkg"; exit 0; } \
  done; echo "no")
endif

ifneq (${WITH_OBSTACK},no)
OBSTACK_CFLAGS = $(shell ${PKG_CONFIG} --cflags ${WITH_OBSTACK}) -DWITH_OBSTACK
OBSTACK_LIBS   = $(shell ${PKG_CONFIG} --libs ${WITH_OBSTACK})
endif

all: ${LIBGCOMPAT_NAME} ${LOADER_NAME}

${LIBGCOMPAT_NAME}: ${LIBGCOMPAT_OBJ}
	${CC} ${CFLAGS} ${LDFLAGS} -shared -Wl,-soname,${LIBGCOMPAT_NAME} \
		-o ${LIBGCOMPAT_NAME} ${LIBGCOMPAT_OBJ} \
		-Wl,--no-as-needed ${LIBUCONTEXT_LIBS} ${OBSTACK_LIBS}

${LIBGCOMPAT_OBJ}: ${LIBGCOMPAT_INCLUDE}

${LOADER_NAME}: ${LOADER_OBJ}
	${CC} ${CFLAGS} ${LDFLAGS} -static -o ${LOADER_NAME} ${LOADER_OBJ}

.c.o:
	${CC} ${CPPFLAGS} ${CFLAGS} -c -D_BSD_SOURCE \
		-DLIBGCOMPAT='"${LIBGCOMPAT_PATH}"' \
		-DLINKER='"${LINKER_PATH}"' -DLOADER='"${LOADER_NAME}"' \
		-fPIC -Ilibgcompat -std=c99 \
		-Wall -Wextra -Wno-frame-address -Wno-unused-parameter \
		${LIBUCONTEXT_CFLAGS} ${OBSTACK_CFLAGS} -o $@ $<

clean:
	rm -f libgcompat/*.o loader/*.o ${LIBGCOMPAT_NAME} ${LOADER_NAME}

format:
	clang-format -i ${LIBGCOMPAT_INCLUDE} ${LIBGCOMPAT_SRC} ${LOADER_SRC}

install: all
	install -D -m755 ${LIBGCOMPAT_NAME} ${DESTDIR}/${LIBGCOMPAT_PATH}
	install -D -m755 ${LOADER_NAME} ${DESTDIR}/${LOADER_PATH}

.PHONY: all clean format install
