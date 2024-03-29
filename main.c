#include "shell.h"

/**
 * handler - hanlder ctrl + c
 * @signal: input
 *
 * Return: void
 */
void handler(int signal);
char *line = NULL, **argVec = NULL, *use_it = NULL;
char *paths = NULL, **paths_arr = NULL;

/**
* main - simple shell
* @argc: number of arguments
* @argv: arguments
* @envp: array of variables
* Return: 0
*/

int main(int argc, char **argv, char **envp)
{
	size_t line_len = 0;
	int id, wstatus;
	ssize_t nread;
	int bol_l, *ptr_bol_l, path_index = 0;
	struct stat st;

	ptr_bol_l = &bol_l;
	(void) argc;
	while (1)
	{
		paths = get_env("PATH", envp);
		paths_arr = _str(paths_arr, paths, ":", 1);
		argVec = give_input(envp, &line, &line_len, &nread,
				argv[0], ptr_bol_l, paths_arr, &path_index);
		if (nread == 1)
		{
			free_all(line, paths, paths_arr, argVec, 0, 1, 1, 0);
			continue;
		}
		if (nread == -9)
		{
			free_all(line, paths, paths_arr, argVec, 1, 1, 1, 1);
			exit(127);
		}
		if (nread == -2)
		{
			free_all(line, paths, paths_arr, argVec, 1, 1, 1, 1);
			exit(0);
		}
		if (nread == -3)
		{
			free_all(line, paths, paths_arr, argVec, 0, 1, 1, 0);
			continue;
		}
		if (stat(argVec[0], &st) != 0 && *ptr_bol_l)
		{
			free_all(line, paths, paths_arr, argVec, 0, 1, 1, 1);
			continue;
		}
		if (*ptr_bol_l == 0)
		{
			use_it = final_path(paths_arr, path_index, argVec[0]);
		}
		id = fork();
		if (*ptr_bol_l == 0)
		{
			run_pro(argv, argVec, use_it, &id, &wstatus);
			free(use_it);
		}
		else
		{
			nread = run_pro(argv, argVec, argVec[0], &id, &wstatus);
		}
		free_all(line, paths, paths_arr, argVec, 0, 1, 1, 1);
	}
	return (0);
}

/**
 * handler - hanlder ctrl + c
 * @signal: input
 *
 * Return: void
 */
void handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		free_all(line, paths, paths_arr, argVec, 1, 1, 1, 0);
		exit(11);
	}
}
