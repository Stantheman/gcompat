====================
 README for gcompat
====================
:Authors:
 * **A. Wilcox**, initial concept, maintainer, lead developer
 * **Adélie Linux and its contributors**, development
:Status:
 Production
:Copyright:
 © 2019 Adélie Linux and contributors.  MIT open source license.

 
.. image:: https://img.shields.io/badge/chat-on%20IRC-blue.svg
   :target: ircs://irc.interlinked.me:6697/#Adelie-Support

.. image:: https://img.shields.io/codacy/grade/1e94efed5989436fa416ede784d4f7b6.svg
   :target: https://app.codacy.com/project/awilfox/gcompat/dashboard

.. image:: https://img.shields.io/badge/license-NCSA-lightgrey.svg
   :target: LICENSE

.. image:: https://repology.org/badge/vertical-allrepos/gcompat.svg
   :target: https://repology.org/project/gcompat/versions


Introduction
============

This distribution contains the implementation of **gcompat**, a library which
provides glibc-compatible APIs for use on musl libc systems.

This library is designed to be used for binaries that are already compiled
against glibc.  It does not contain any headers, and cannot be used to build
software that requires glibc.  It is instead recommended that any software that
requires glibc APIs be modified to become more portable.

This library can optionally be compiled with other libraries to make a single,
unfied solution.  This can include fts_, libucontext_, obstack_, and others.

*gcompat* additionally provides a loader stub.  This is a small library that
has the same name as the glibc dynamic linker on glibc platforms; when a binary
is run that uses glibc as its dynamic linker, the stub will run, redirecting it
to use musl and automatically preloading the gcompat library.


.. _fts: https://github.com/pullmoll/musl-fts/
.. _libucontext: https://code.foxkit.us/adelie/libucontext/
.. _obstack: https://github.com/pullmoll/musl-obstack/


License
```````
This library is provided under the NCSA open source license.


Changes
```````
Any changes to this repository must be reviewed before being pushed to the
master branch.  There are no exceptions to this rule.  For security-sensitive
updates, contact the Security Team at sec-bugs@adelielinux.org.



Background
==========

Many applications distributed for Linux are built against glibc.
Unfortunately, many of glibc's internals are leaked out in to the resultant
binary which makes it difficult or impossible to run these binaries on systems
using the `musl libc`_.

While the goal of Adélie Linux is to support only true Libre Software that can
be built from source code, we recognise that some users may require the ability
to run pre-compiled binaries on their computers.  This may include older
software that does not compile with modern compilers, or non-libre software
such as firmware or device management software.

.. _`musl libc`: http://www.musl-libc.org/



Supported Environments
======================
The following architectures are supported:

* x86 (32-bit)

  This is a Tier 1 architecture in the Adélie Linux system, as *pmmx*.

* x86_64

  This is a Tier 1 architecture in the Adélie Linux system.

* armv6+ (as ``arm``)

  This is a Tier 2 architecture in the Adélie Linux system, as *armv6* and
  *armv7*.  As such, it may not receive thorough testing.

* aarch64

  This is a Tier 1 architecture in the Adélie Linux system.

* s390x

  This architecture is **not supported** by the Adélie Linux system.  It is
  *untested* by the release team and may not be functional.

The following architectures utilise a Linux kernel syscall:

* ppc (32-bit)

  This is a Tier 1 architecture in the Adélie Linux system.

* ppc64

  This is a Tier 1 architecture in the Adélie Linux system.  Only the ELFv2 ABI
  is supported, and only Big Endian modes of operation are tested by the
  release team.



Building
========

In order to build correctly, the gcompat build system requires a few details
about the host environment, regarding both the musl host and glibc target.  To
provide this information to the build system, you will need to set the
following variables or pass them to ``make``.

* ``LINKER_PATH``

  The location of the musl ELF interpreter.  On PowerPC, this is
  ``/lib/ld-musl-powerpc64.so.1``.

* ``LOADER_NAME``

  The location of the glibc ELF interpreter.  On PowerPC, this is
  ``ld.so.2``.

You may additionally specify any of the following optional variables for
further customisation:

* ``DESTDIR``

  The directory in which to install files.  The default value is ``/``.

* ``LIBGCOMPAT_PATH``

  The location in which to install ``libgcompat.so``, relative to ``DESTDIR``.
  The default value is ``/lib/libgcompat.so.0``.

* ``LOADER_PATH``

  The location in which to install the glibc interpreter stub.  The default
  value is ``/lib/$LOADER_NAME``.

* ``WITH_LIBUCONTEXT``

  Determines whether to build with libucontext_.

For example, on an x86_64 musl host and x86_64 glibc target, you may run:

    $ make LINKER_PATH=/lib/ld-musl-x86_64.so.1 LOADER_NAME=ld-linux-x86-64.so.2

    $ make LINKER_PATH=/lib/ld-musl-x86_64.so.1 LOADER_NAME=ld-linux-x86-64.so.2 install

Please note that unlike libucontext, the gcompat build system does *not*
attempt to guess the correct values for you.  This feature may be added later.



Usage
=====

Running binaries linked against glibc
-------------------------------------

If the values specified during build were correct, programs built for glibc
should run normally on your musl host.  If they are not working, check the
program's ELF interpreter entry, using scanelf(8) like so:

``
$ scanelf -i ~/glibcfile
 TYPE   INTERP FILE
ET_EXEC /lib64/ld-linux-x86-64.so.2 /home/kaniini/glibcfile
``

If the interpreter path is different than expected, use PatchELF or install a
symlink from ``LOADER_PATH`` to the specified interpreter.


Using glibc binaries via dlopen(3) from a musl program
------------------------------------------------------

There are two ways to accomplish this:

* You can add libgcompat.so to the DT_NEEDED entries in the ELF that you want
  to have the gcompat symbols available in.  Use a tool such as PatchELF for
  this.

* Alternatively, you can link the musl binary against libgcompat.

Environment variables
---------------------

* ``GLIBC_FAKE_VERSION``

  The value of ``GLIBC_FAKE_VERSION`` will be returned as the result of
  ``gnu_get_libc_version``.  The current default is "2.8".

* ``GLIBC_FAKE_DEBUG``

  Setting this variable will cause dlmopen and dlvsym to display the overrides
  they are performing, and may cause additional output to stderr with other
  functions in the future.




Reporting Issues
================

gcompat is released by the Adélie Linux project in the hopes that it is useful
to the community.  Current issues may be found at our BTS_; you may also
`submit an issue`_ there.

For general discussion, questions, or to submit a patch, please use the
`gcompat mailing list`_.

.. _BTS: https://bts.adelielinux.org/buglist.cgi?product=gcompat&resolution=---
.. _`submit an issue`: https://bts.adelielinux.org/enter_bug.cgi?product=gcompat
.. _`gcompat mailing list`: https://lists.adelielinux.org/postorius/lists/gcompat.lists.adelielinux.org/
