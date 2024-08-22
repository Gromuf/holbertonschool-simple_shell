#include "main.h"
#include <ctype.h>

/**
 * check_absolute_path - Checks if the command is an absolute path.
 * @cmd: The command to check.
 *
 * Description: Checks if the command is an absolute path and executable.
 *
 * Return: A string containing the absolute path if executable, or NULL.
 */
char *check_absolute_path(const char *cmd)
{
	if (cmd[0] == '/')
	{
		if (is_executable(cmd))
		{
			return (strdup(cmd));
		}
	}
	return (NULL);
}

/**
 * check_current_directory - Checks if the command exists in
 * the current directory.
 * @cmd: The command to locate.
 *
 * Return: A string containing the full path if found in the current directory,
 * or NULL.
 */
char *check_current_directory(const char *cmd)
{
	char full_path[1024];
	char *cwd = getcwd(NULL, 0);

	if (cwd == NULL)
	{
		perror("getcwd");
		return (NULL);
	}

	snprintf(full_path, sizeof(full_path), "%s/%s", cwd, cmd);
	free(cwd);

	if (is_executable(full_path))
	{
		return (strdup(full_path));
	}

	return (NULL);
}

/**
 * check_path_directories - Searches for the command
 * in directories listed in PATH.
 * @cmd: The command to locate.
 *
 * Return: A string containing the full path if found in PATH directories
 * , or NULL.
 */
char *check_path_directories(const char *cmd)
{
	char full_path[1024];
	char *path_copy = strdup(PATH1);
	char *token;

	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
		if (is_executable(full_path))
		{
			free(path_copy);
			return (strdup(full_path));
		}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

/**
 * parse_exit_status - Parses the exit status from the command
 * @cmd: The command string
 *
 * Return: The exit status (default is 0)
 */
int parse_exit_status(char *cmd)
{
	char *arg = cmd + 4;  /* Move pointer past "exit" */
	int status = 0;
	int i;

	while (*arg == ' ')  /* Skip any spaces after "exit" */
		arg++;

	if (*arg != '\0')  /* If there is something after "exit" */
	{
		for (i = 0; arg[i]; i++)
		{
			if (!isdigit(arg[i]))  /* Check if the argument is not a digit */
			{
				return (0);  /* Return 0 to keep the shell running */
			}
		}
		status = atoi(arg);  /* Convert the argument to an integer */
	}

	return (status);
}
