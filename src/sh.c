#include <err.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define JD297_VEC_IMPLEMENTATION
#include "vec.h"

#include "exit.h"

vector_t args;
char *cmd = NULL;
int code = 0;
char *code_str = NULL;

extern void sh_free();

void sh_free()
{
	free(cmd);
	free(code_str);
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
			if (args.num == 1) {
				int length = snprintf(NULL, 0, "%d", code) + 1;

				if ((code_str = malloc(length)) == NULL) {
					err(EXIT_FAILURE, "malloc");
				}

				snprintf(code_str, length, "%d", code);

				vec_set(&args, 1, code_str);
				++args.num;
			}

			code = sh_built_in_exit(args.num, (char **)args.elements);
		}

		next: {
			args.num = 0;

			free(cmd);
		}
	}

	return code;
}
