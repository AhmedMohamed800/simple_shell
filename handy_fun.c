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
char *give_input(char **line, size_t *line_len, ssize_t *nread, struct stat st,
		char *message)
{
	size_t size_of_message = size_of(message);
	char **argVec, *d = {" "};

	argVec = malloc(sizeof(char *));
	if (isatty(STDIN_FILENO)) // fix non interactive
	{	
		if (write(STDOUT_FILENO, "#cisfun$ ", 9) == -1)
			perror("Error2"), exit(99);
	}
	*nread = getline(line, line_len, stdin);
	if (*nread == EOF)
		write(STDOUT_FILENO,"\n",1), exit(1);
	else if (*nread == -1)
		perror("Error1"), exit(69);
	(*line)[*nread - 1] = '\0';
	*argVec = strtok(*line, d);
	if (stat(*argVec, &st) != 0)
	{
		write(STDERR_FILENO, message, size_of_message);
		if (isatty(STDIN_FILENO)) // fix non interactve
		{
			write(STDERR_FILENO, ":", 2);
			perror("");
		}
		else
		{
			write(STDERR_FILENO, ": 1:", 5);
			write(STDERR_FILENO, *line, size_of(*line));
			write(STDERR_FILENO, ":", 2);
			write(STDERR_FILENO, "not found\n", 10);
			exit (99);
		}
	}
	return(*line);
}

/**
* run_pro - execute a program and handle fork
* @line: string
* @line_len: line's length
* @id: fork id
* @wstatus: wait status
`* Return: nothing
*/
void run_pro(char **argv, char **line, size_t *line_len, int *id, int *wstatus)
{
	char **argVec, *envVec[] = {NULL}, *d = {" "};
	int words, i;
	
	words = count_words(*line);
	argVec = malloc(sizeof(char *) * words);
	argVec[0] = *line;
	for (i = 1; i < words; i++)
		argVec[i] = strtok(NULL, d), write(STDOUT_FILENO,"here\n",6);
	if (*id == -1)
		perror("Error11"), exit(97);
	if (*id == 0)
	{
		if (execve(argVec[0], argVec, envVec) == -1)
		{
			write(STDERR_FILENO, *argv, size_of(*argv));
			write(STDERR_FILENO,": 1:", 5);
			perror(*line), exit(99);
		}
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

