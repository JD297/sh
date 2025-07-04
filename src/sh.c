#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define JD297_VEC_IMPLEMENTATION
#include "vec.h"

#include "cd.h"
#include "colon.h"
#include "exit.h"
#include "false.h"
#include "true.h"
#include "unset.h"

#include "getline.h"

vector_t args;
char *cmd = NULL;
int code = 0;
char *code_str = NULL;

extern void sh_free(void);

void sh_free(void)
{
	free(cmd);
	free(code_str);
	vec_free(&args);
}

int main(void)
{
	vec_init(&args);

	if (atexit(sh_free) != 0) {
		return EXIT_FAILURE;
	}

	while ((cmd = sh_getline("sh: ")) != NULL) {
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

			code = sh_built_in_exit(args.num, (char **)vec_begin(&args));
		}
		else if (strcmp(":", *vec_begin(&args)) == 0) {
			code = sh_built_in_colon(args.num, (char **)vec_begin(&args));
		}
		else if (strcmp("true", *vec_begin(&args)) == 0) {
			code = sh_built_in_true(args.num, (char **)vec_begin(&args));
		}
		else if (strcmp("false", *vec_begin(&args)) == 0) {
			code = sh_built_in_false(args.num, (char **)vec_begin(&args));
		}
		else if (strcmp("cd", *vec_begin(&args)) == 0) {
			code = sh_built_in_cd(args.num, (char **)vec_begin(&args));
		}
		else if (strcmp("unset", *vec_begin(&args)) == 0) {
			code = sh_built_in_unset(args.num, (char **)vec_begin(&args));
		}
		else {
			pid_t pid;

			if ((pid = fork()) == -1) {
				err(EXIT_FAILURE, "fork");
			}

			if (pid == 0) {
				if (execvp(*vec_begin(&args), (char **)vec_begin(&args)) == -1) {
					err(EXIT_FAILURE, "%s", (char *)*vec_begin(&args));
				}
			}

			int wstatus;

			if (waitpid(pid, &wstatus, 0) == -1) {
				err(EXIT_FAILURE, "waitpid");
			}

			code = WEXITSTATUS(wstatus);
		}

		next: {
			args.num = 0;

			free(cmd);
		}
	}

	return code;
}
