#include "shell.h"

/**
* _str - Handle command lines with arguments
* @arr: array of strings
* @line: line to be diveded
* Return: array of string
*/
char **_str(char **arr, char *line)
{
	char *token;
	int i = 0;

	arr = malloc(sizeof(char *) * size_of(line, 1));
	if (arr == NULL)
		perror("Error"), exit(90);
	token = strtok(line, " ");
	while (token != NULL)
	{
		arr[i] = malloc(size_of(token, 0) + 1);
		if (arr[i] == NULL)
			perror("Error"), exit(90);
		_strcpy(arr[i], token);
		token = strtok(NULL, " ");
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
		struct stat *st, char *message)
{
	size_t size_of_message = size_of(message, 0);
	char **argVec;

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
	argVec = _str(argVec, *line);
	if (stat(argVec[0], st) != 0)
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
void run_pro(char **argv, char **argVec, int *id, int *wstatus)
{
	char *envVec[] = {NULL};

	if (*id == -1)
		perror("Error"), exit(97);
	if (*id == 0)
	{
		if (execve(argVec[0], argVec, envVec) == -1)
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

