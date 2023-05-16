:wq#include "shell.h"

/**
* main - simple shell
* @argc: number of arguments
* @argv: arguments
* Return: 0
*/
int main(int argc, char **argv)
{
	char *line = NULL;
	char **argVec;
	struct stat st;
	size_t line_len = 0;
	int id, wstatus;
	ssize_t nread;
	int d = 0;

	while (1)
	{
		argVec = give_input(&line, &line_len, &nread, st, argv[0]);
		if (stat(argVec[0], &st) != 0)
			continue;
		id = fork();
		run_pro(argv, argVec, &id, &wstatus);
	}
	return (0);
}
