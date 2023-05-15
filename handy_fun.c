#include "shell.h"

/**
* size_of - gives the value of a string
* @str: string to be misured
* Return: size of a string
*/
size_t size_of(char *str)
{
	size_t i = 0;

	while (*str++)
		i++;
	return (i);
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
void give_input(char **line, size_t *line_len, ssize_t *nread, struct stat st,
		char *message)
{
	size_t size_of_message = size_of(message);

	if (isatty(STDIN_FILENO)) // fix non interactive
	{	
		if (write(STDOUT_FILENO, "#cisfun$ ", 9) == -1)
			perror("Error2"), exit(99);
	}
	*nread = getline(line, line_len, stdin);
	if (*nread == -1)
		perror("Error1"), exit(98);
	(*line)[*nread - 1] = '\0';
	if (stat(*line, &st) != 0)
	{
		write(STDERR_FILENO, message, size_of_message);
		if (isatty(STDIN_FILENO)) // fix non interactve
		{
			write(STDERR_FILENO, ":", 2);
			perror("");
		}
		else
		{
			write(STDERR_FILENO, " 1:", 4);
			write(STDERR_FILENO, *line, size_of(*line));
			write(STDERR_FILENO, ":", 2);
			perror("");
			exit (99);
		}
	}
}

/**
* run_pro - execute a program and handle fork
* @line: string
* @line_len: line's length
* @id: fork id
* @wstatus: wait status
`* Return: nothing
*/
void run_pro(char **line, size_t *line_len, int *id, int *wstatus)
{
	char *argVec[] = {NULL}, *envVec[] = {NULL};

	if (*id == -1)
		perror("Error11"), exit(97);
	if (*id == 0)
	{
		if (execve(*line, argVec, envVec) == -1)
			perror("Error10"), exit(99); // non interactive
	}
	else
	{
		wait(wstatus);
		free(*line);
		*line = NULL;
		*line_len = 0;
		if (!isatty(STDIN_FILENO))
			exit (10);	
	}
}
