#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Macro pour le chemin par défaut */
#define PATH1 "/usr/local/bin:/usr/bin:/bin:/custom/path"

extern char **environ;

/*_getenv.c*/
char *_getenv(const char *name);

/*_strtok_r.c*/
char *_strtok_r(char *str, const char *delim, char **saveptr);

/*_which.c*/
char *which(const char *cmd);

/*exec_cmd.c*/
int is_empty_cmd(char *cmd);
int parse_command_args(char *cmd_copy, char **argv);
char *get_command_path(char *argv[]);
int execute_command(char *path_copy, char *argv[], char *cmd_copy);
int exec_cmd(char *cmd);

/*exec_multiple_cmd.c*/
void exec_multiple_cmd(char *cmd);

/*handle_which_path.c*/
char *check_absolute_path(const char *cmd);
char *check_current_directory(const char *cmd);
char *check_path_directories(const char *cmd);

/*path.c*/
char *normalize_path(const char *path);
int file_exists(const char *path);
void handle_command_not_found(char *cmd);
int is_executable(const char *path);
char *construct_relative_path(const char *filename);

/*string_function.c*/
char *_strchr(const char *s, int c);
int _strcmp(const char *s1, const char *s2);
size_t _strcspn(const char *s1, const char *s2);
char *_strdup(const char *s);
size_t _strlen(const char *s);

/*subfunction.c*/
void display_prompt(void);
int is_interactive(void);
int _isspace(int c);
char *read_cmd(void);

#endif
