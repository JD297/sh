#ifndef JD297_SH_GETLINE_H
#define JD297_SH_GETLINE_H

#ifdef GETLINE_LIBREADLINE

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#define sh_getline(promt) readline((promt))

#endif

#ifdef GETLINE_LIBC

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

char *sh_getline(const char *promt)
{
	char *line = NULL;
	size_t size;
	ssize_t nread;

	printf("%s", promt);
	fflush(stdout);

	if ((nread = getline(&line, &size, stdin)) == -1) {
		putchar('\n');
		free(line);
		return NULL;
	}

	line[nread-1] = '\0';

	return line;
}

#endif

#ifdef GETLINE_LIBEDITLINE

#error "NOT IMPLEMENTED"

#endif

#endif
