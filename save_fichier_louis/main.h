#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h> /* Inclure pour struct stat et les constantes S_IXUSR */

/* Macro pour le chemin par défaut */
#define PATH1 "/usr/local/bin:/usr/bin:/bin:/custom/path"
/*#define PATH1 "bin:sbin:/usr/bin:/usr/local/bin"*/

/* Prototypes des fonctions */
void display_prompt(void);

char *read_cmd(void);

/*void exec_cmd(char *cmd);*/

size_t _strcspn(const char *s1, const char *s2);

int is_interactive(void);

void exec_multiple_cmd(char *cmd);

int is_empty_cmd(char *cmd);

/*int _isspace(char c);*/
int _isspace(int c);

extern int should_exit; /* Déclaration de la variable globale exit e */

void exit(int status);

/*char *find_executable(const char *cmd);*/

int is_executable(const char *path);

char *which(const char *cmd);

int _isspace(int c);

char *_strtok_r(char *str, const char *delim, char **saveptr);
char *my_strtok(char *str, const char *delim);

int exec_cmd(char *cmd);

int file_exists(const char *path);

void handle_command_not_found(char *cmd);

char *construct_relative_path(const char *cmd);

/*char *which(char *cmd)*/

/*extern int should_exit;*/

int _strcmp(const char *s1, const char *s2);
char *_strchr(const char *s, int c);
char *_strdup(const char *s);
size_t _strlen(const char *s);
char *_getenv(const char *name);
/*void set_default_path();*/
void set_PATH1(void);
char *normalize_path(const char *path);

/*int my_setenv(const char *name, const char *value, int overwrite);*/

/*int main(int argc, char *argv[]);*/

#endif
