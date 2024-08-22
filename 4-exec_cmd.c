#include "main.h"

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
		if (!_isspace((unsigned char)*cmd))
			return (0);
		cmd++;
	}
	return (1);
}

/**
 * parse_command_args - Parses a command string into arguments.
 * @cmd_copy: A copy of the command string to be parsed.
 * @argv: An array to store the parsed arguments.
 *
 * Return: The number of arguments parsed.
 */
int parse_command_args(char *cmd_copy, char **argv)
{
	char *token;
	int argc = 0;

	token = strtok(cmd_copy, " \n");
	while (token != NULL && argc < 1023)
	{
		argv[argc++] = token;
		token = strtok(NULL, " \n");
	}
	argv[argc] = NULL;

	return (argc);
}

/**
 * get_command_path - Determines the path of a command.
 * @argv: An array of command arguments, with argv[0] being the command.
 *
 * Return: A string containing the command path if found, or NULL if not.
 */
char *get_command_path(char *argv[])
{
	char *path_copy = NULL;
	char *env_path = _getenv("PATH");

	if (env_path == NULL || strlen(env_path) == 0)
	{
		if (strchr(argv[0], '/') != NULL)
		{
			path_copy = strdup(argv[0]);
		}
		else
		{
			handle_command_not_found(argv[0]);
			return (NULL);
		}
	}
	else
	{
		path_copy = (argv[0][0] == '/')
						? strdup(argv[0])
						: which(argv[0]);
	}

	if (!path_copy || !is_executable(path_copy))
	{
		handle_command_not_found(argv[0]);
		free(path_copy);
		exit(2);
	}

	return (path_copy);
}

/**
 * execute_command - Forks a process and executes a command.
 * @path_copy: The path of the command to be executed.
 * @argv: An array of command arguments.
 * @cmd_copy: A copy of the original command string.
 *
 * Return: The status code of the executed command.
 */
int execute_command(char *path_copy, char *argv[], char *cmd_copy)
{
	pid_t pid;
	int status = 0;

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
			exit(EXIT_FAILURE);
		}
	}
	else /* Parent process */
	{
		waitpid(pid, &status, 0);
	}

	return (status);
}

/**
 * exec_cmd - Executes a shell command.
 * @cmd: The command string to be executed.
 *
 * Return: The status code of the executed command, or an error code.
 */
int exec_cmd(char *cmd)
{
	char *argv[1024];
	int status = 0;
	char *cmd_copy = strdup(cmd);
	char *path_copy;

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

	parse_command_args(cmd_copy, argv);
	if (argv[0] != NULL)
	{
		if (strcmp(argv[0], "exit") == 0)
		{
			free(cmd_copy);
			exit(EXIT_SUCCESS);
		}

		path_copy = get_command_path(argv);
		if (!path_copy)
		{
			free(cmd_copy);
			return (127);
		}

		status = execute_command(path_copy, argv, cmd_copy);
		free(path_copy);
	}

	free(cmd_copy);
	return (status);
}
