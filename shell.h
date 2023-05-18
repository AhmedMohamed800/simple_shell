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
		char *message, char **envp,
		char *final_path, int *bol_main, char **paths);
void run_pro(char **argv, char **argVec, int *id, int *wstatus,
		int *bol_main, char *final_path);
size_t size_of(char *str, size_t spaces);
char *_strcpy(char *dest, char *src);
void _free_array(char **arr);
char **_str(char **arr, char *line, const char *delim, int check);
char *get_env(char *identi, char **envp);
int handle_path(char **envp, char *final_path, 
		char *argVec_first, char **paths_arr);

#endif
