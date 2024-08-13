#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> /*non defini dans std89*/
#include <errno.h>

/*display_prompt.c*/
void display_prompt(void);

/*read_cmd.c*/
char *read_cmd(void);

/*exec_cmd.c*/
void exec_cmd(char *cmd);

#endif
