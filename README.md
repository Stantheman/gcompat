# gcompat

The gcompat project provides a glibc-compatible runtime environment for distributions that use musl libc.

It provides a compatibility library as well as a loader which injects the compatibility library.  The loader
is installed where the glibc ELF interpreter (`/lib/ld-linux.so.2`) would normally be, allowing for execution
of glibc programs to work in the same way as native musl programs.


## building gcompat

In order to build correctly, the gcompat build system requires a few details about the host environment, both
from the musl end, as well as the glibc end.  These are:

| Variable           | Description                                                                                       |
|--------------------|---------------------------------------------------------------------------------------------------|
| `LINKER_PATH`      | The location of the musl ELF interpreter.                                                         |
| `LOADER_NAME`      | The name of the glibc ELF interpreter that would be appropriate for your architecture.            |
| `LIBGCOMPAT_PATH`  | *optional* The location to install the libgcompat.so library to.  Usually `/lib/libgcompat.so.0`. |
| `LOADER_PATH`      | *optional* The location to install the loader to.  Usually `/lib/${LOADER_NAME}`.                 |
| `WITH_LIBUCONTEXT` | *optional* Whether or not to build against `libucontext`.                                         |

For example on x86_64 musl with x86_64 glibc compatibility, you would want to do:

```
$ make LINKER_PATH=/lib/ld-musl-x86_64.so.1 LOADER_NAME=ld-linux-x86-64.so.2
$ make LINKER_PATH=/lib/ld-musl-x86_64.so.1 LOADER_NAME=ld-linux-x86-64.so.2 install
```

The `DESTDIR` environment variable is available for the convenience of packagers.


## running programs under gcompat

Assuming everything is in the right place, the programs should just work.  If they are not working, check the program's
ELF interpreter entry, using scanelf(8) like so:

```
$ scanelf -i ~/glibcfile
 TYPE   INTERP FILE
ET_EXEC /lib64/ld-linux-x86-64.so.2 /home/kaniini/glibcfile
```

If the interpreter path is different than expected, use PatchELF or install a symlink to the interpreter.


## making musl programs accept glibc binaries for dlopen(3)

You have two options:

* You can add libgcompat.so to the DT_NEEDED entries in the ELF that you want to have the gcompat symbols available in.
  Use a tool such as PatchELF for this.

* Alternatively, you can link the musl binary against libgcompat.


## special environment variables

* `GLIBC_FAKE_VERSION` will override the result of `gnu_get_libc_version`, which currently defaults to "2.8".
* `GLIBC_FAKE_DEBUG` will cause dlmopen and dlvsym to display the overrides they are performing, and may cause
  additional output to stderr with other functions in the future.

## reporting issues

If you are having issues with gcompat, please report them at our [bug tracker](https://bts.adelielinux.org/).

## contributing

If you want to contribute code or documentation, please see the CONTRIBUTING.rst file in this repository.
