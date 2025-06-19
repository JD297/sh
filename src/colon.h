#include <stdlib.h>

extern int sh_built_in_colon(int argc, char **argv);

int sh_built_in_colon(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return EXIT_SUCCESS;
}
