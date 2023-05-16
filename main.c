#include "shell.h"

/**
* main - simple shell
* @argc: number of arguments
* @argv: arguments
* Return: 0
*/
int main(int argc, char **argv)
{
	char *line = NULL;
	struct stat st;
	size_t line_len = 0;
	int id, wstatus;
	ssize_t nread;

	while (1)
	{
		line = give_input(&line, &line_len, &nread, st, argv[0]);
		if (stat(line, &st) != 0)
			continue;
		id = fork();
		run_pro(argv,&line, &line_len, &id, &wstatus);
	}
	return (0);
}
