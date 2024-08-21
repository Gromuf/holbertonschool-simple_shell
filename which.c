#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * which - Locate a command in the directories listed in PATH.
 * @cmd: The command to locate.
 *
 * Description: This function searches through the directories listed
 * in the PATH environment variable to find the full path of the given
 * command. It returns a string with the full path if found, or NULL
 * if the command is not found or an error occurs.
 *
 * Return: A string containing the full path to the command if found,
 *         or NULL if not found.
 */
char *which(const char *cmd)
{
	char full_path[1024];
	char *cwd = getcwd(NULL, 0);
	char *path_copy;
	char *token;

	if (cwd == NULL)
	{
		perror("getcwd");
		return (NULL);
	}

	/* Check if the command is an absolute path or relative path */
	if (cmd[0] == '/')
	{
		if (is_executable(cmd))
		{
			free(cwd);
			return (strdup(cmd));
		}
	}
	else
	{
		/* Check in current directory */
		snprintf(full_path, sizeof(full_path), "%s/%s", cwd, cmd);
		if (is_executable(full_path))
		{
			free(cwd);
			return (strdup(full_path));
		}

		/* Check in PATH directories */
		path_copy = strdup(PATH1);
		if (path_copy == NULL)
		{
			perror("strdup");
			free(cwd);
			return (NULL);
		}

		token = my_strtok(path_copy, ":");
		while (token != NULL)
		{
			snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
			if (is_executable(full_path))
			{
				free(path_copy);
				free(cwd);
				return (strdup(full_path));
			}
			token = my_strtok(NULL, ":");
		}

		free(path_copy);
	}

	free(cwd);
	return (NULL);
}
