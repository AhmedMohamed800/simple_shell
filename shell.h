#ifndef __SHELL__
#define __SHELL__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

char **give_input(char **line, size_t *line_len, ssize_t *nread,
		struct stat *st, char *message);
void run_pro(char **argv, char **argVec, int *id, int *wstatus);
size_t size_of(char *str, size_t spaces);
char *_strcpy(char *dest, char const *src);
void _free_array(char **arr);
char **_str(char **arr, char *line);

#endif
