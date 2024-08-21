#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/*#define PATH_DELIM ':'*/

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

	token = my_strtok(path_copy, ":");
	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
		if (is_executable(full_path))
		{
			free(path_copy);
			return (strdup(full_path));
		}
		token = my_strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
