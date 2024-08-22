#include "main.h"

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
	char *path;

	path = check_absolute_path(cmd);
	if (path != NULL)
	{
		return (path);
	}

	path = check_current_directory(cmd);
	if (path != NULL)
	{
		return (path);
	}

	return (check_path_directories(cmd));
}
