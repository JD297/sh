#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern int sh_built_in_exit(int argc, char **argv);

static void sh_built_in_exit_usage(char **argv)
{
	fprintf(stderr, "Usage: %s [n]\n", argv[0]);
}

int sh_built_in_exit(int argc, char **argv)
{
	int opt;
	int code = 0;

	while ((opt = getopt(argc, argv, "")) != -1) {
		switch (opt) {
			default:
				sh_built_in_exit_usage(argv);
				exit(EXIT_FAILURE);
		}
	}

	if (optind < argc) {
		code = atoi(argv[optind]);
	}

	exit(code);
}
