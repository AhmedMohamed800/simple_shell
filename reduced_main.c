#include "shell.h"

/**
* @handle_path - handle the path
* @line: asd
*
*/
int handle_path(char **envp, char *final_path, char *argVec_first, char **paths_arr)
{
	char *ptr;
	int bol_l = 0, i = 0, size_of_first = size_of(argVec_first, 0);
	int size_of_path, j = 0;
	struct stat *st;
	
	while (paths_arr[i] != NULL)
	{
		size_of_path = size_of(paths_arr[i], 0);
		final_path = malloc(size_of_first + size_of_path + 2);
		if (final_path == NULL)
			perror("Error"), exit(98);
		ptr = paths_arr[i];
		for(j = 0; ptr[j]; j++)
		{
			final_path[j] = ptr[j];
		}
		_strcpy(final_path, argVec_first);
		if (stat(final_path, st) != 0)
		{
			bol_l = 1;
			break;
		}
		i++;
		free(final_path);
		final_path = NULL;
	}
	return (bol_l);
}

/**
* _str - Handle command lines with arguments
* @arr: array of strings
* @line: line to be diveded
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
		perror("Error11"), exit(90);
	token = strtok(line, delim);
	while (token != NULL)
	{
		arr[i] = malloc(size_of(token, 0) + 1);
		if (arr[i] == NULL)
			perror("Error2"), exit(90);
		_strcpy(arr[i], token);
		token = strtok(NULL, delim);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

/**
* give_input - reads input from user
* @line: enterd input
* @line_len: line's length
* @nread: read the value of line
* @st: struct for stat
* @message: the argv[0] ./example
* Return: nothing
*/
char **give_input(char **line, size_t *line_len, ssize_t *nread,
		char *message, char **envp, 
		char *final_path, int *bol_main, char **paths)
{
	size_t size_of_message = size_of(message, 0);
	char **argVec = NULL;
	struct stat *st;

	if (isatty(STDIN_FILENO))
	{
		if (write(STDOUT_FILENO, "#cisfun$ ", 9) == -1)
			perror("Error"), exit(99);
	}
	*nread = getline(line, line_len, stdin);
	if (*nread == EOF)
		write(STDOUT_FILENO, "\n", 1), exit(1);
	else if (*nread == -1)
		perror("Error"), exit(69);
	(*line)[*nread - 1] = '\0';
	argVec = _str(argVec, *line, " ", 0);
	*bol_main = handle_path(envp, final_path, argVec[0], paths);
	if (stat(argVec[0], st) != 0 && bol_main)
	{
		write(STDERR_FILENO, message, size_of_message);
		if (isatty(STDIN_FILENO))
		{
			write(STDERR_FILENO, ": ", 3);
			perror("");
		}
		else
		{
			write(STDERR_FILENO, ": 1:", 5);
			write(STDERR_FILENO, *line, size_of(*line, 0));
			write(STDERR_FILENO, ":", 2);
			write(STDERR_FILENO, "not found\n", 10);
			exit(99);
		}
	}
	return (argVec);
}

/**
* run_pro - execute a program and handle fork
* @argv: arguments from user input
* @id: fork id
* @wstatus: wait status
* @argVec: arguments to pass in execve
* Return: nothing
*/
void run_pro(char **argv, char **argVec, int *id,
		int *wstatus, int *bol_main, char *final_path)
{
	char *envVec[] = {NULL};

	if (*id == -1)
		perror("Error"), exit(97);
	if (*id == 0)
	{
		if (*bol_main == 1)
		{
			if (execve(final_path, argVec, envVec) == -1)
			{
				write(STDERR_FILENO, argv, size_of(*argv, 0));
				write(STDERR_FILENO, ": 1: ", 6);
				perror(argVec[0]), exit(99);
			}
		}
		else
		{
			if (execve(argVec[0], argVec, envVec) == -1)
			{
				write(STDERR_FILENO, argv, size_of(*argv, 0));
				write(STDERR_FILENO, ": 1: ", 6);
				perror(argVec[0]), exit(99);
			}
		}
	}
	else
	{
		wait(wstatus);
		if (!isatty(STDIN_FILENO))
			exit(10);
	}
}
