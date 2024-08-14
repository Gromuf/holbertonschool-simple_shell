#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>  /* Inclure pour struct stat et les constantes S_IXUSR */


/* Prototypes des fonctions */
void display_prompt(void);

char *read_cmd(void);

void exec_cmd(char *cmd);

size_t _strcspn(const char *s1, const char *s2);

int is_interactive(void);

void exec_multiple_cmd(char *cmds);

int is_empty_cmd(char *cmd);

int _isspace(char c);

extern int should_exit; /* Déclaration de la variable globale exit e */

void exit(int status);

/*char *find_executable(const char *cmd);*/

int is_executable(const char *path);

char *which(const char *filename);

extern int should_exit;


/*int main(int argc, char *argv[]);*/

#endif
