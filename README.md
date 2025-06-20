# sh

shell, the standard command language interpreter

## make

### commands

- clean
- install
- uninstall
- tests

### flags

The Makefile can be configured by setting the well known flags:

- CC       (default: cc)
- CFLAGS   (default: -Wall -Wextra -Wpedantic -g)
- LDFLAGS  (default: )
- TARGET   (default: sh)
- PREFIX   (default: /usr/local)
- BINDIR   (default: $(PREFIX)/bin)
- MANDIR   (default: $(PREFIX)/share/man)
- BUILDDIR (default: build)

And the special option:
- GETLINE  (see sections: libc (default), lreadline, leditline)

An example would be to make with optimations (level 3), no debug (-g) which is
default and libs are staticlly linked. The execution would be in build/jd297sh.

```sh
make CFLAGS=-O3 LDFLAGS=-static TARGET=jd297sh
```

#### libc (default)

The default only requires libc as a dependency.

This build will not implement the specifications of the following:

- [Command History List](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/sh.html#tag_20_117_13_01)
- [Command Line Editing](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/sh.html#tag_20_117_13_02)

```sh
make
```

#### lreadline

```sh
make LDFLAGS="-lreadline -ltinfo" GETLINE=GETLINE_LIBREADLINE
```

#### leditline

```sh
make LDFLAGS="-ledit" GETLINE=GETLINE_LIBEDITLINE
```
