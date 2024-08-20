#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PATH_DELIM ':'
/*#define PATH1 "bin:sbin:/usr/bin:/usr/local/bin"   Remplacez ceci par une valeur fixe de PATH pour la simulation*/

/* Utility function to resolve relative paths */
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

/**
 * which - Recherche le chemin complet d'un fichier exécutable dans PATH.
 *
 * @cmd: Le nom du fichier à rechercher.
 *
 * Description:
 * Cette fonction recherche le fichier spécifié par `cmd` dans les répertoires listés
 * dans la variable d'environnement `PATH`. Pour chaque répertoire dans `PATH`, elle
 * construit le chemin complet vers le fichier et vérifie si le fichier est exécutable
 * en utilisant la fonction `is_executable`.
 *
 * Return:
 * Retourne un pointeur vers une chaîne de caractères contenant le chemin complet
 * du fichier si le fichier est trouvé et exécutable. Sinon, retourne NULL. La chaîne
 * de caractères allouée dynamiquement doit être libérée par l'appelant.
 */
/* Fonction qui imite le comportement de 'which' */
char *which(const char *cmd)
{
	char full_path[1024];
	char *cwd = getcwd(NULL, 0);
	/*char *path1 = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"; Example PATH*/
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
			return strdup(cmd);
		}
	}
	else
	{
		/* Check in current directory */
		snprintf(full_path, sizeof(full_path), "%s/%s", cwd, cmd);
		if (is_executable(full_path))
		{
			free(cwd);
			return strdup(full_path);
		}

		/* Check in PATH directories */
		path_copy = strdup(PATH1);
		if (path_copy == NULL)
		{
			perror("strdup");
			free(cwd);
			return NULL;
		}

		token = my_strtok(path_copy, ":");
		while (token != NULL)
		{
			snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
			if (is_executable(full_path))
			{
				free(path_copy);
				free(cwd);
				return strdup(full_path);
			}
			token = my_strtok(NULL, ":");
		}

		free(path_copy);
	}

	free(cwd);
	return (NULL);
}
