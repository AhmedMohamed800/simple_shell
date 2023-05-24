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
#include <signal.h>

int _strcp(char *a, char *b);
char **give_input(char **envp, char **line, size_t *line_len, ssize_t *nread,
		char *message, int *bol_main,
		char **paths, int *path_index);
ssize_t run_pro(char **argv, char **argVec, char *use_it,
		int *id, int *wstatus);
size_t size_of(char *str, size_t spaces);
char *_strcpy(char *dest, char *src);
void _free_array(char **arr);
char **_str(char **arr, char *line, const char *delim, int check);
char *get_env(char *identi, char **envp);
int handle_path(char *argVec_first, char **paths_arr, int *path_index);
char *final_path(char **paths_arr, int index, char *first_argvec);
void free_all(char *line, char *paths, char **paths_arr, char **argVec,
		int line_l, int paths_l, int arr_l, int vec_l);
void handler(int signal);
size_t handle_not_found(char *argVec, int bol_main,
		char *message, size_t size_of_message, char *line);

#endif
