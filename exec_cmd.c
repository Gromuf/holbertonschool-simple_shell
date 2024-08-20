#include "main.h"
#include <string.h>
#include <stdlib.h> /*for strtok_r*/
#include <unistd.h> /*for execve and fork*/
#include <stdio.h>
#include <sys/wait.h>
#include <stddef.h>
#include <ctype.h>	  /* for isspace*/
#include <sys/stat.h> /* for stat*/

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
	char *token;
	int argc = 0;
	int status = 0;
	char *path_copy = NULL;
	char *cmd_copy = strdup(cmd);
	char *env_path;

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

	token = my_strtok(cmd_copy, " \n");
	while (token != NULL && argc < 1023)
	{
		argv[argc++] = token;
		token = my_strtok(NULL, " \n");
	}
	argv[argc] = NULL;

	if (argv[0] != NULL)
	{
		/* Handle 'exit' command without arguments */
		if (strcmp(argv[0], "exit") == 0)
		{
			free(cmd_copy);
			exit(EXIT_SUCCESS);
		}

		/* Check if PATH is empty */
		env_path = _getenv("PATH");
		if (env_path == NULL || strlen(env_path) == 0)
		{
			/* PATH is empty, check if command contains '/' */
			if (strchr(argv[0], '/') != NULL)
			{
				/* Command includes a path */
				path_copy = strdup(argv[0]);
			}
			else
			{
				/* Command does not include a path, cannot execute */
				handle_command_not_found(argv[0]);
				free(cmd_copy);
				return (127);
			}
		}
		else
		{
			/* PATH is not empty */
			path_copy = (argv[0][0] == '/') ? strdup(argv[0]) : which(argv[0]);
		}

		if (!path_copy || !is_executable(path_copy))
		{
			handle_command_not_found(argv[0]);
			free(cmd_copy);
			free(path_copy);
			return (127);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(cmd_copy);
			free(path_copy);
			return (EXIT_FAILURE);
		}

		if (pid == 0) /* Child process */
		{
			if (execve(path_copy, argv, NULL) == -1)
			{
				perror("execve");
				free(cmd_copy);
				free(path_copy);
				exit(127); /*Retourner 127 en cas d'échec d'exécution*/
			}
		}
		else /* Parent process */
		{
			waitpid(pid, &status, 0);
		}

		free(path_copy);
	}

	free(cmd_copy);
	return (status);
}

/**
 * set_file_permissions - Change the permissions of a file.
 * @path: The path to the file or directory.
 * @mode: The new permissions for the file or directory (octal mode).
 *
 * Return: 0 on success, -1 on failure with errno set.
 */
int set_file_permissions(const char *path, mode_t mode)
{
	if (chmod(path, mode) == -1)
	{
		perror("chmod");
		return (-1);
	}
	return (0);
}
