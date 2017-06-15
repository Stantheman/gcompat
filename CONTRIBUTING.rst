===================================
 Contribution Guide for libgcompat
===================================
:Author:
  * **A. Wilcox**, documentation writer
:Copyright:
  © 2016-2017 Adélie Linux and contributors.  NCSA open source licence.




Introduction
============

This repository contains the libgcompat, a library providing GNU libc (glibc)
compatibility for Linux computers using the musl libc.




Code style
==========

Contributions are expected to maintain a consistent code style.  This ensures
readable and future maintainability, since all the code will look and feel the
same.  A few key notes about the C style used in this repository:


Include comments
````````````````

When using the ``#include`` preprocessor directive, add a comment next to it
detailing the interfaces used from that header.  For example:

```
#include <stdlib.h>     // getenv
```


Tabs
````

Hard tabs (\t) are used, and are 8 spaces.  Where brace alignment is required,
tabs are used to the nearest eighth space, followed by the requisite number of
spaces.


Braces
``````

**Always** use braces for blocks like ``if``, ``while``, ``for``, even if the
block only contains a single statement.  This is to ensure that more complex
decision trees do not have accidental side-effects.




Contributing Changes
====================

This section describes the usual flows of contribution to this repository.


GitLab Pull Requests
````````````````````

#. If you do not already have a GitLab account, you must create one.

#. Create a *fork* of the packages repository.  For more information, consult
   the GitLab online documentation.

#. Clone your forked repository to your computer.

#. Make your changes.

#. Test your changes to ensure they are correct.

#. Add (or remove) changed files using ``git add`` and ``git rm``.

#. Commit your changes to the tree using the command ``git commit`` and
   ``git push``.

#. Visit your forked repository in a Web browser.

#. Choose the *Create Pull Request* button.

#. Review your changes to ensure they are correct, and then submit the form.


Mailing List
````````````

#. Clone the packages repository to your computer.

#. Make your changes.

#. Test your changes to ensure they are correct.

#. Add (or remove) changed files using ``git add`` and ``git rm``.

#. Commit your changes to the tree using the command ``git commit``.

#. Use the command ``git format-patch HEAD^`` to create a patch file for your
   commit.

   .. note:: If you have made multiple commits to the tree, you will need to
             add an additional ^ for each commit you have made.  For example,
             if you have made three commits, you will use the command
             ``git format-patch HEAD^^^``.

#. Email the resulting patch to the adelie-dev@lists.adelielinux.org mailing
   list, or use ``git send-email``.
