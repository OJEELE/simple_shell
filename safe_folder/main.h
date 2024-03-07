#ifndef MAIN_H
#define MAIN_H

/* libraries */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

/* prototypes */
void shell_interactive(void);
void shell_non_interactive(void);
int execute_args(char **args);
char *read_line(void);
char **split_line(char *line);
int new_process(char **args);
int own_cd(char **args);
int own_exit(char **args);
int own_env(char **args);
int own_help(char **args);
extern char **environ;
char *read_stream(void);
#endif /* MAIN_H */
