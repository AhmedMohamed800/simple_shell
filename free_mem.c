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
*
*
*
*/
void handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		exit (90);
	}
}
