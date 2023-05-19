#include "shell.h"

/**
*
*
*
*/
char *final_path(char **paths_arr, int index, char *first_argvec)
{
	size_t path_size = size_of(paths_arr[index], 0);
	size_t argVec_size = size_of(first_argvec, 0), i = 0, j = 0;
	char *final_path = NULL, *ptr = NULL;

	ptr = paths_arr[index];
	final_path = malloc(path_size + argVec_size + 2);
	if (final_path == NULL)
		perror("Error"), exit (69);
	for (i = 0; ptr[i]; i++)
	{
		final_path[i] = ptr[i];
	}
	final_path[i] = '/';
	i += 1;
	for (j = 0; first_argvec[j]; j++, i++)
	{
		final_path[i] = first_argvec[j];
	}
	final_path[i] = '\0';
	return (final_path);
}
