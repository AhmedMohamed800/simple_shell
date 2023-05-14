#include "shell.h"

/**
* main - simple shell
* Return: 0
*/
int main(void)
{
	char *line = NULL;
	size_t line_len = 0;
	int id;
	int *wstatus;
	ssize_t nread;
	char *argVec[] = {NULL};
	char *envVec[] = {NULL};

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$", 9);
		nread = getline(&line, &line_len, stdin);
		line[nread - 1] = '\0';
		id = fork();
		if (id == 0)
		{
			execve(line, argVec, envVec);
		}
		else
		{
			wait(wstatus);
			free(line);
		}
	}
}
