#include "shell.h"

/**
* free_all - best way to free memory
* @line: line to free
* @paths: paths to free
* @paths_arr: paths array to free
* @argVec: argVec arr to free
* @line_l: 1 if line should be freed
* @paths_l: 1 if paths_l should be freed
* @arr_l: 1 if arr_1 should be freed
* @vec_l: 1 if vec_l should be freed
* Return: nothing
*/
void free_all(char *line, char *paths, char **paths_arr, char **argVec,
		int line_l, int paths_l, int arr_l, int vec_l)
{
	if (line_l == 1)
		free(line);
	if (paths_l == 1)
		free(paths);
	if (arr_l == 1)
		_free_array(paths_arr);
	if (vec_l == 1)
		_free_array(argVec);
}

/**
* run_pro - execute a program and handle fork
* @argv: arguments from user input
* @id: fork id
* @use_it: input
* @wstatus: wait status
* @argVec: arguments to pass in execve
* Return: nothing
*/
void run_pro(char **argv, char **argVec, char *use_it, int *id, int *wstatus)
{
	char *envVec[] = {NULL};

	if (*id == -1)
		perror("Error"), exit(97);
	if (*id == 0)
	{
		if (execve(use_it, argVec, envVec) == -1)
		{
			write(STDERR_FILENO, argv, size_of(*argv, 0));
			write(STDERR_FILENO, ": 1: ", 6);
			perror(argVec[0]), exit(99);
		}
	}
	else
	{
		wait(wstatus);
		if (!isatty(STDIN_FILENO))
			exit(10);
	}
}
