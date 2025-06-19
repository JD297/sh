#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#define JD297_VEC_IMPLEMENTATION
#include "vec.h"

#include "exit.h"

vector_t args;
char *cmd = NULL;
int code = 0;

extern void sh_free();

void sh_free()
{
	free(cmd);
	vec_free(&args);
}

int main()
{
	vec_init(&args);

	if (atexit(sh_free) != 0) {
		return EXIT_FAILURE;
	}

	while ((cmd = readline("sh: ")) != NULL) {
		if (*cmd == '\0') {
			goto next;
		}

		for (char *rst = cmd; ; rst = NULL) {
				if (vec_push_back(&args, strtok(rst, " ")) == -1) {
					return EXIT_FAILURE;
				}

				if (vec_at_last(&args) == NULL) {
					--args.num;
					break;
				}
		}

		if (vec_begin(&args) == NULL) {
			goto next;
		}

		if (strcmp("exit", *vec_begin(&args)) == 0) {
			code = sh_built_in_exit(args.num, (char **)args.elements);
		}

		next: {
			args.num = 0;

			free(cmd);
		}
	}

	return code;
}
