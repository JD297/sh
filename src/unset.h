#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "macro.h"

int sh_built_in_unset(int argc, char **argv);

static void sh_built_in_unset_usage(char **argv);

static void sh_built_in_unset_usage(char **argv)
{
	fprintf(stderr, "Usage: %s [-fv] name...\n", argv[0]);
}

int sh_built_in_unset(int argc, char **argv)
{
	int opt;
	OPTIND_RESET();
	int fflag = 0;
	int vflag = 0;

	while ((opt = getopt(argc, argv, "fv")) != -1) {
		switch (opt) {
			case 'f':
				fflag = 1;
				break;
			case 'v':
				vflag = 1;
				break;
			default:
				sh_built_in_unset_usage(argv);
				return EXIT_FAILURE;
		}
	}

	if ((fflag == 1 && vflag == 1) || optind == argc) {
		sh_built_in_unset_usage(argv);
		return EXIT_FAILURE;
	}

	for (int i = optind; i < argc; ++i) {
		if (fflag == 1) {
			assert(0 && "not implemented: unset a function (-f)");
		}
		else {
			unsetenv(argv[i]);
		}
	}

	return EXIT_SUCCESS;
}
