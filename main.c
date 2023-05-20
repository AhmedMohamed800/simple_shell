#include "shell.h"

/**
* main - simple shell
* @argc: number of arguments
* @argv: arguments
* @envp: array of variables
* Return: 0
*/
int main(int argc, char **argv, char **envp)
{
	char *line = NULL, **argVec = NULL;
	size_t line_len = 0;
	int id, wstatus;
	ssize_t nread;
	int bol_l, *ptr_bol_l, path_index = 0;
	struct stat st;
	char *paths = get_env("PATH", envp), **paths_arr = NULL;

	ptr_bol_l = &bol_l;
	paths_arr = _str(paths_arr, paths, ":", 1);
	(void) argc;
	while (1)
	{
		argVec = give_input(&line, &line_len, &nread,
				argv[0], ptr_bol_l, paths_arr, &path_index);
		if (nread == 1)
			continue;
		if (stat(argVec[0], &st) != 0 && *ptr_bol_l)
			continue;
		if (!(*ptr_bol_l == 1) && stat(argVec[0], &st) == 0)
			argVec[0] = final_path(paths_arr, path_index, argVec[0]);
		id = fork();
		run_pro(argv, argVec, &id, &wstatus);
		free(line);
		line = NULL;
		line_len = 0;
		_free_array(argVec);
	}
	free(paths_arr);
	free(paths);
	return (0);
}
