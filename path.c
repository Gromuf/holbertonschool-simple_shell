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
	char *path;
	char *dir;
	char full_path[1024];
	char *result = NULL;

	/* Déclaration des variables au début */
	path_env = getenv("PATH");
	if (!path_env)
	{
		return (NULL);
	}

	path = strdup(path_env); /*Dupliquer la variable d'environnement PATH*/
	if (!path)
	{
		perror("strdup");
		exit(EXIT_FAILURE); /*Gestion des erreurs d'allocation mémoire*/
	}

	dir = strtok(path, ":");
	while (dir != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			result = strdup(full_path); /*Trouvé l'exécutable*/
			break;
		}
		dir = strtok(NULL, ":");
	}

	free(path); /* Libération de la mémoire allouée pour `path`*/
	return (result);
}
