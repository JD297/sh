#include <stdlib.h>

extern int sh_built_in_false(int argc, char **argv);

int sh_built_in_false(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return EXIT_FAILURE;
}
