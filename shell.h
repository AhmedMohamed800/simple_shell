#ifndef __SHELL__
#define __SHELL__

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>

int _strcp(char *a, char *b);
char **give_input(char **envp, char **line, size_t *line_len, ssize_t *nread,
		char *message, int *bol_main,
		char **paths, int *path_index);
void run_pro(char **argv, char **argVec, int *id, int *wstatus);
size_t size_of(char *str, size_t spaces);
char *_strcpy(char *dest, char *src);
void _free_array(char **arr);
char **_str(char **arr, char *line, const char *delim, int check);
char *get_env(char *identi, char **envp);
int handle_path(char *argVec_first, char **paths_arr, int *path_index);
char *final_path(char **paths_arr, int index, char *first_argvec);


#endif
