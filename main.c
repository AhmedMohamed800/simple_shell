#include "shell.h"

/**
* main - simple shell
* @argc: number of arguments
* @argv: arguments
* Return: 0
*/
int main(int argc, char **argv, char **envp)
{
	char *line = NULL;
	char **argVec;
	size_t line_len = 0;
	int id, wstatus;
	ssize_t nread;
	char *final_path;
	int *bol_main;
	struct stat *st;
	char *paths = get_env("PATH", envp);
	char **paths_arr = _str(paths_arr, paths, ":", 1);

	(void) argc;
	while (1)
	{
		argVec = give_input(&line, &line_len, &nread,
				argv[0], envp, final_path, bol_main, paths_arr);
		if (stat(argVec[0], st) != 0 && bol_main)
			continue;
		id = fork();
		run_pro(argv, argVec, &id, &wstatus, bol_main, final_path);
		free(final_path);
		final_path = NULL;
		free(line);
		line = NULL;
		line_len = 0;
		_free_array(argVec);
	}
	return (0);
}
