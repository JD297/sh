#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "macro.h"

static char *sh_built_in_cd_program_invocation_name;

int sh_built_in_cd(int argc, char **argv);

static void sh_built_in_cd_usage(char **argv);

static int sh_built_in_cd_cd(const char *path, const char arg);

static int sh_built_in_cd_cd(const char *path, const char arg)
{
	(void)arg;

	if (setenv("OLDPWD", getenv("PWD"), 1) == -1) {
		fprintf(stderr, "%s: %s\n", sh_built_in_cd_program_invocation_name, strerror(errno));
		return EXIT_FAILURE;
	}

	// TODO CDPATH

	if (arg == 'P') {
		// TODO
	}

	if (chdir(path) == -1) {
		fprintf(stderr, "%s: %s\n", sh_built_in_cd_program_invocation_name, strerror(errno));
		return EXIT_FAILURE;
	}

	if (setenv("PWD", path, 1) == -1) {
		fprintf(stderr, "%s: %s\n", sh_built_in_cd_program_invocation_name, strerror(errno));
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

static void sh_built_in_cd_usage(char **argv)
{
	fprintf(stderr, "Usage: %s [-L|-P] [directory]\n", argv[0]);
	fprintf(stderr, "       %s -\n", argv[0]);
}

int sh_built_in_cd(int argc, char **argv)
{
	sh_built_in_cd_program_invocation_name = argv[0];

	int opt;
	OPTIND_RESET();
	char arg = 'L';
	char *path;

	while ((opt = getopt(argc, argv, "LP:")) != -1) {
		switch (opt) {
			case 'L':
			case 'P':
				arg = opt;
				break;
			default:
				sh_built_in_cd_usage(argv);
				return EXIT_FAILURE;
		}
	}

	if (argc >= 2) {
		if (strcmp(argv[1],"-") == 0) {
			if (argc == 2) {
				int code;
				char *path = getenv("OLDPWD");

				if ((code = sh_built_in_cd_cd(path, arg)) == 0) {
					printf("%s\n", path);
				}

				return code;
			} else {
				fprintf(stderr, "%s: %s\n", sh_built_in_cd_program_invocation_name, "too many arguments");
				sh_built_in_cd_usage(argv);
				return EXIT_FAILURE;
			}
		}
	}

	if (optind < argc) {
		path = argv[optind];
	} else {
		path = getenv("HOME");

		if (path == NULL) {
			fprintf(stderr, "%s: %s\n", sh_built_in_cd_program_invocation_name, "HOME is not set");
			return EXIT_FAILURE;
		}
	}

	return sh_built_in_cd_cd(path, arg);
}
