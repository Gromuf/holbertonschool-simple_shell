#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
/*#define PATH_DELIM ':'*/

/**
 * normalize_path - Resolves an absolute path from a given relative path.
 * @path: The relative path to be resolved.
 *
 * Description: This function uses the `realpath` system call to convert
 * the provided relative path into an absolute path. If `realpath` fails,
 * it prints an error message and returns NULL.
 *
 * Return: A string containing the absolute path if successful,
 *         or NULL if the path cannot be resolved.
 */
char *normalize_path(const char *path)
{
	char *resolved_path = realpath(path, NULL);

	if (resolved_path == NULL)
	{
		perror("realpath");
		return (NULL);
	}
	return (resolved_path);
}

/**
 * file_exists - Checks if a file exists at the given path.
 * @path: The path to the file.
 *
 * This function uses the `stat` system call to check whether
 * a file exists at the specified path. It returns 1 if the
 * file exists, and 0 if it does not exist.
 *
 * Return: 1 if the file exists, 0 otherwise.
 */
int file_exists(const char *path)
{
	struct stat buffer;

	return (stat(path, &buffer) == 0);
}

/**
 * handle_command_not_found - Handles the "command not found" error.
 * @cmd: The command that was not found.
 *
 * This function is called when a command cannot be executed
 * because it is not found in the system's PATH or in the
 * specified location. It prints an appropriate error message
 * to the standard error output, indicating that the command
 * was not found.
 *
 * Return: void.
 */
void handle_command_not_found(char *cmd)
{
	fprintf(stderr, "./hsh: 1: %s: not found\n", cmd);
}

/**
 * is_executable - Checks if a file is executable.
 * @path: The path of the file to check.
 *
 * Return: 1 if the file is executable, otherwise 0.
 */
int is_executable(const char *path)
{
	return (access(path, X_OK) == 0);
}

/**
 * construct_relative_path - Constructs a relative path for a given filename.
 * @filename: The name of the file for which to construct the relative path.
 *
 * This function creates a relative path string by prepending the necessary
 * directory levels (e.g., `../`) to the given filename. The resulting path
 * allows access to a file located in the parent or higher-level directories.
 * The caller is responsible for freeing the memory allocated for the returned
 * string.
 *
 * Return: A pointer to the dynamically allocated string containing the
 *         relative path, or NULL if memory allocation fails.
 */
char *construct_relative_path(const char *filename)
{
	char *path = malloc(1024);

	if (path == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	snprintf(path, 1024, "../../%s", filename);
	return (path);
}

