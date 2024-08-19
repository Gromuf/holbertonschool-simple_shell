#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stddef.h>

/*#include <stdbool.h>  Inclure pour le type bool*/

/*extern int should_exit;  Variable globale pour control la sortie du shell*/
/*int should_exit = 0; Variable globale pour contrôler la sortie du shell */

/**
 * exec_multiple_cmd - Executes multiple commands from a string.
 * @cmd: The string containing commands separated by newlines.
 *
 * This function splits the input string into individual commands
 * and executes each command using exec_cmd. Each command is
 * processed in a separate child process.
 */
/*void exec_multiple_cmd(char *cmd)*/
void exec_multiple_cmd(char *cmd)
{
	char *line;
	const char delim[2] = "\n";
	char *saveptr;

	line = _strtok_r(cmd, delim, &saveptr);

	while (line != NULL)
	{
		if (!is_empty_cmd(line))
			exec_cmd(line);
		line = _strtok_r(NULL, delim, &saveptr);
	}
}

/**
 * is_empty_cmd - Checks if a command string is empty or contains only
 * whitespace.
 *
 * @cmd: A pointer to the command string to be checked.
 *
 * Return: 1 if the command is empty or contains only whitespace,
 *         0 otherwise.
 */
int is_empty_cmd(char *cmd)
{
	while (*cmd)
	{
		/*if (_isspace((unsigned char)*cmd) == 0)*/
		if (!_isspace((unsigned char)*cmd))
			return (0);
		cmd++;
	}
	return (1);
}

/**
 * exec_cmd - Executes a command in a new process.
 * @cmd: The command to be executed.
 *
 * This function creates a new process using fork(). If the fork is
 * successful, the child process attempts to execute the specified
 * command using execve(). If execve() fails, an error message is
 * printed. The parent process waits for the child process to finish
 * execution.
 */
/*void exec_cmd(char *cmd)*/
int exec_cmd(char *cmd)
{
	pid_t pid;
	char *argv[1024];
	char *token = strtok(cmd, " \n");
	int argc = 0;
	int status;
	/*static int last_exit_status = 0;*/
	char *path_copy = NULL;
	char *cmd_copy = strdup(cmd);

	if (!cmd_copy)
	{
		perror("strdup");
		return (EXIT_FAILURE);
	}

	if (is_empty_cmd(cmd))
	{
		free(cmd_copy);
		return (0);
	}

	while (token != NULL && argc < 1023)
	{
		argv[argc++] = token;
		token = strtok(NULL, " \n");
	}
	argv[argc] = NULL;

	if (argv[0] != NULL)
	{
		/*Handle 'exit' command without arguments*/
		if (strcmp(argv[0], "exit") == 0)
		{
			/*int exit_status = (argv[1] != NULL) ? atoi(argv[1]) : last_exit_status;*/
			free(cmd_copy);
			/*exit(exit_status);*/
			exit(EXIT_SUCCESS); /* Exit without error*/
		}

		path_copy = (argv[0][0] == '/') ? strdup(argv[0]) : which(argv[0]);
		if (!path_copy)
		{
			path_copy = construct_relative_path(argv[0]);
		}

		if (!path_copy || !is_executable(path_copy) || !file_exists(path_copy))
		{
			/*printf("./hsh: 1: ");*/
			handle_command_not_found(argv[0]);
			free(cmd_copy);
			/*free(path_copy);*/
			/*return (status);*/
			return (127);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			free(cmd_copy);
			free(path_copy);
			return (EXIT_FAILURE);
		}

		if (pid == 0) /* Child process */
		{
			if (execve(path_copy, argv, NULL) == -1)
			{
				perror(path_copy);
				free(cmd_copy);
				free(path_copy);
				exit(EXIT_FAILURE);
			}
		}
		else /* Parent process */
		{
			/*Attendre que le processus enfant se termine*/
			while (waitpid(pid, &status, WUNTRACED) > 0 && !WIFEXITED(status) && !WIFSIGNALED(status)) {
			/*On peut ajouter un traitement supplémentaire ici si nécessaire*/
		}

			/* Traiter le statut de sortie du processus enfant*/
			if (WIFEXITED(status) && WEXITSTATUS (status) == 127)
			{
				printf("Le processus s'est terminé avec le code de sortie %d\n", WEXITSTATUS(status));
				exit(127); /*use 127 to signal command not found*/
			}
			else if (WIFSIGNALED(status))
			{
				printf("Le processus a été terminé par le signal %d\n", WTERMSIG(status));
			}

			/*do*/
			/*{*/
			/*	waitpid(pid, &status, WUNTRACED);*/
			/*} while (!WIFEXITED(status) && !WIFSIGNALED(status));*/

			/*if (WIFEXITED(status))*/
			/*{*/
			/*	last_exit_status = WEXITSTATUS(status);*/
			/*}*/
			/*else if (WIFSIGNALED(status))*/
			/*{*/
			/*	last_exit_status = 128 + WTERMSIG(status);*/
			/*}*/
		}

		free(path_copy);
	}

	free(cmd_copy);
	return (status);
}
