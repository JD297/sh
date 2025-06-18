#include <readline/readline.h>
#include <stdlib.h>
#include <string.h>
#define JD297_VEC_IMPLEMENTATION
#include "vec.h"

#include "exit.h"

int main()
{
	vector_t args;

	vec_init(&args);

	char *cmd = NULL;

	while ((cmd = readline("sh: ")) != NULL) {
		if (*cmd == '\0') {
			goto next;
		}

		for (char *rst = cmd; ; rst = NULL) {
				if (vec_push_back(&args, strtok(rst, " ")) == -1) {
					// TODO error handle
				}

				if (vec_at_last(&args) == NULL) {
					break;
				}
		}

		if (vec_begin(&args) == NULL) {
			goto next;
		}

		if (strcmp("exit", *vec_begin(&args)) == 0) {
			//free(cmd); // TODO memory leak

			sh_built_in_exit(args.num - 1, (char **)args.elements);
		}

		next: {
			args.num = 0;

			free(cmd);
		}
	}

	vec_free(&args);

	return 0;
}
