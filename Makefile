.POSIX:

CC            = cc
CFLAGS        = -Wall -Wextra -Wpedantic -g
LDFLAGS       = -lreadline

TARGET        = sh
PREFIX        = /usr/local
BINDIR        = $(PREFIX)/bin
MANDIR        = $(PREFIX)/share/man
SRCDIR        = src
BUILDDIR      = build

BUILDINS      = $(SRCDIR)/exit.h $(SRCDIR)/colon.h $(SRCDIR)/true.h $(SRCDIR)/false.h $(SRCDIR)/cd.h

$(BUILDDIR)/$(TARGET): $(BUILDDIR)/sh.o
	$(CC) $(CFLAGS) $(BUILDDIR)/sh.o -o $@ $(LDFLAGS)

$(BUILDDIR)/sh.o: $(SRCDIR)/sh.c $(SRCDIR)/vec.h $(BUILDINS)
	$(CC) $(CFLAGS) -c $(SRCDIR)/sh.c -o $@

clean:
	rm -f $(BUILDDIR)/*

install: $(TARGET)
	cp $(BUILDDIR)/$(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	rm -f $(BINDIR)/$(TARGET)

tests: $(BUILDDIR)/$(TARGET)
	TARGET=$(BUILDDIR)/$(TARGET) testsh --test
