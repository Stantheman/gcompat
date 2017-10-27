==========================
 Changelog for libgcompat
==========================
:Author:
  * **A. Wilcox**, documentation writer
  * **Contributors**, code
:Copyright:
  © 2016-2017 Adélie Linux and contributors.  NCSA open source licence.




0.2.0 (Not Yet Released)
========================

Build system
------------

* Ensure correct compilation on GCC 4.x.


sysctl
------

* Don't build where SYS__sysctl is not defined (at least aarch64), credit to
  Michael Gehring of VoidLinux for finding this error.




0.1.0 (2017-10-15)
==================

ucontext
--------
* new module

* Adds getcontext(), which always sets errno to ENOSYS and returns -1.


resolv
------
* new module

* Adds res_ninit and res_nclose methods which wrap around standard
  res_init and res_close.


string
------
* Adds strtoll_l and strtoull_l 'locale-aware' methods.  Currently, these
  do nothing but call the non-locale-aware versions as musl does not implement
  `LC_NUMERIC`.


malloc
------
* Adds __libc_memalign which is a thin shim to musl's __memalign.

* Adds __libc_malloc, __libc_calloc, __libc_realloc, and __libc_free which are
  used by some system-level software.  These just call directly to musl's free
  and malloc/calloc/realloc.


math
----
* Adds non-prefixed isinf, isinff, isnan, and isnanf, needed since these are
  implemented as macros in musl.


Build system
------------
* A patch from Daniel James of VoidLinux has been applied, which allows use of
  CC instead of hard-coding `gcc`.


Documentation
-------------
* Updates the README.

* Adds contribution guide, a copy of the license, and this changelog.


pthread
-------
* Adds __pthread_register_cancel and __pthread_unregister_cancel stubs, which
  do nothing because they are not relevant to musl's pthread implementation.

* Adds __register_atfork stub.

* Removes pthread_setname_np since musl now provides it.


pwd
---
* new module

* Adds getpwent_r and fgetpwent_r.


sysctl
------
* new module

* Adds sysctl.
