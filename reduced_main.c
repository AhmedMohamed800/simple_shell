#include "shell.h"

/**
* handle_path - handle the path
* @argVec_first: the first element of argVec array
* @paths_arr: array of paths
* @path_index: the index of the path in which there is our path
* Return: 0 if it's found and 1 if it's not found
*/
int handle_path(char *argVec_first, char **paths_arr, int *path_index)
{
	char *ptr;
	int bol_l = 1, i = 0;
	size_t size_of_first = size_of(argVec_first, 0);
	int size_of_path, j = 0, g = 0;
	struct stat st;
	char *final_path = NULL;

	if (argVec_first[0] == '/' ||
			(argVec_first[0] == '.' && argVec_first[1] == '/'))
		return (1);
	while (paths_arr[i] != NULL)
	{
		size_of_path = size_of(paths_arr[i], 0);
		final_path = malloc(size_of_first + size_of_path + 2);
		if (final_path == NULL)
			perror("Error"), exit(98);
		ptr = paths_arr[i];
		for (j = 0; ptr[j]; j++)
		{
			final_path[j] = ptr[j];
		}
		final_path[j] = '/';
		j += 1;
		for (g = 0; argVec_first[g]; g++)
		{
			final_path[j] = argVec_first[g];
			j++;
		}
		final_path[j] = '\0';
		if (stat(final_path, &st) == 0)
		{
			bol_l = 0;
			free(final_path);
			break;
		}
		i++;
		free(final_path);
	}
	*path_index = i;
	return (bol_l);
}

/**
* _str - Handle command lines with arguments
* @arr: array of strings
* @line: line to be diveded
* @delim: delimater
* @check: 0 for spaces and else for :
* Return: array of string
*/
char **_str(char **arr, char *line, const char *delim, int check)
{
	char *token;
	int i = 0;

	if (check == 0)
	{
		arr = malloc(sizeof(char *) * size_of(line, 1));
	}
	else
	{
		arr = malloc(sizeof(char *) * size_of(line, 2));
	}
	if (arr == NULL)
		perror("Error"), exit(90);
	token = strtok(line, delim);
	while (token != NULL)
	{
		arr[i] = malloc(size_of(token, 0) + 1);
		if (arr[i] == NULL)
			perror("Error"), exit(90);
		_strcpy(arr[i], token);
		token = strtok(NULL, delim);
		i++;
	}

	arr[i] = NULL;
	return (arr);
}

/**
* give_input - reads input from user
* @envp: input
* @line: enterd input
* @line_len: line's length
* @nread: read the value of line
* @message: the argv[0] ./example
* @bol_main: to determine whether the path is found or not
* @paths: arr of paths
* @path_index: the index of choosend path
* Return: nothing
*/
char **give_input(char **envp, char **line, size_t *line_len, ssize_t *nread,
		char *message, int *bol_main, char **paths, int *path_index)
{
	size_t size_of_message = size_of(message, 0);
	char **argVec = NULL;

	if (isatty(STDIN_FILENO))
	{
		if (write(STDOUT_FILENO, "#cisfun$ ", 9) == -1)
			perror("Error"), exit(99);
	}
	signal(SIGINT, handler);
	if (signal(SIGINT, handler) == SIG_ERR)
		perror("Error");
	*nread = getline(line, line_len, stdin);
	if (*nread == EOF)
	{
		*nread = -2;
		return (NULL);
	}
	(*line)[*nread - 1] = '\0';
	if (*nread == 1)
		return (NULL);
	if (!_strcp(*line, "exit"))
	{
		*nread = -2;
		return (NULL);
	}
	if (!_strcp(*line, "env"))
	{
		while (*envp)
		{
			write(STDOUT_FILENO, *envp, size_of(*envp, 0)), envp++;
			write(STDOUT_FILENO, "\n", 1);
		}
		*nread = -3;
		return (NULL);
	}
	argVec = _str(argVec, *line, " ", 0);
	*bol_main = handle_path(argVec[0], paths, path_index);
	handle_not_found(argVec[0], *bol_main, message, size_of_message,
			*line);
	return (argVec);
}

/**
* handle_not_found - handle errors not found
* @argVec: first elemtns of argVec array
* @bol_main: bol_main test
* @message: the massage to be printed
* @size_of_message: message's size
* @line: the line gotten from getline
* Return: nothing
*/
void handle_not_found(char *argVec, int bol_main, char *message,
		size_t size_of_message, char *line)
{
	struct stat st;

	if (stat(argVec, &st) != 0 && bol_main == 1)
	{
		write(STDERR_FILENO, message, size_of_message);
		if (isatty(STDIN_FILENO))
			write(STDERR_FILENO, ": ", 3), perror("");
		else
		{
			write(STDERR_FILENO, ": 1: ", 6);
			write(STDERR_FILENO, line, size_of(line, 0));
			write(STDERR_FILENO, ": ", 3);
			write(STDERR_FILENO, "not found\n", 10), exit(99);
		}
	}
}

/**
 * _strcp - compare 2 strings
 * @a: first strign
 * @b: sec string
 *
 * Return: 0 if they are the same otherwise 1
 */
int _strcp(char *a, char *b)
{
	int size_a, size_b;

	size_a = size_of(a, 0);
	size_b = size_of(b, 0);
	if (size_a != size_b)
		return (1);
	while (*a)
	{
		if (*a != *b)
			return (1);
		a++;
		b++;
	}
	return (0);
}
