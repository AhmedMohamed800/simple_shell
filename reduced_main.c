#include "shell.h"

/**
* give_input - reads input from user
* @line: enterd input
* @line_len: line's length
* @nread: read the value of line
* @st: struct for stat
* @message: the argv[0] ./example
* Return: nothing
*/
char **give_input(char **line, size_t *line_len, ssize_t *nread, struct stat st,
		char *message)
{
	size_t size_of_message = size_of(message, 0), i = 0;
	char **argVec, *token;

	if (isatty(STDIN_FILENO))
	{	
		if (write(STDOUT_FILENO, "#cisfun$ ", 9) == -1)
			perror("Error"), exit(99);
	}
	*nread = getline(line, line_len, stdin);
	if (*nread == EOF)
		write(STDOUT_FILENO,"\n",1), exit(1);
	else if (*nread == -1)
		perror("Error"), exit(69);
	(*line)[*nread - 1] = '\0';
	argVec = malloc(sizeof(char *) * size_of(*line, 1));
	if (argVec == NULL)
		perror("Error"), exit(90);
	token = strtok(*line, " ");
	while (token != NULL)
	{
		argVec[i] = malloc(size_of(token, 0));
		if (argVec[i] == NULL)
			perror("Error"), exit(90);
		_strcpy(argVec[i], token);
		token = strtok(NULL, " ");
		i++;
	}
	argVec[i] = NULL;
	if (stat(argVec[0], &st) != 0)
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
			exit (99);
		}
	}
	free(*line);
	*line = NULL;
	return (argVec);
}

/**
* run_pro - execute a program and handle fork
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
			write(STDERR_FILENO,": 1: ", 6);
			perror(argVec[0]), exit(99);
		}
	}
	else
	{
		wait(wstatus);
		_free_array(argVec);
		if (!isatty(STDIN_FILENO))
			exit (10);	
	}
}

