#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 1024

/**
 * find_executable - Locate the full path of an executable file.
 * @cmd: The name of the executable to locate.
 *
 * This function searches for an executable file in the directories listed in
 * the PATH environment variable. It constructs the full path by appending
 * the executable name to each directory in PATH and checks if the file exists
 * and is executable.
 *
 * Return: A pointer to a dynamically allocated string containing the full path
 *         of the executable if found. The caller is responsible for freeing
 *         the allocated memory. If the executable is not found or an error
 *         occurs, NULL is returned.
 */
char *find_executable(const char *cmd)
{
	char *path_env;
	char *path_copy;
	char *dir;
	char full_path[MAX_PATH_LENGTH];
	struct stat st;

	/* Retrieve the PATH environment variable */
	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		fprintf(stderr, "PATH environment variable is not set.\n");
		return (NULL);
	}

	/* Make a copy of the PATH variable to tokenize */
	path_copy = strdup(path_env);
	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}

	/* Tokenize the PATH variable and check each directory */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);

		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
		{
			free(path_copy);
			return strdup(full_path);
		}

		dir = strtok(NULL, ":");
	}

	fprintf(stderr, "Command not found: %s\n", cmd);
	free(path_copy);
	return (NULL);
}
