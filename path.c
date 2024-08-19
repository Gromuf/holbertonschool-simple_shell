#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/*#define PATH1_DELIM ':'*/
/*#define PATH1 "bin:sbin:/usr/bin:/usr/local/bin"   Remplacez ceci par une valeur fixe de PATH pour la simulation*/

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
	static char path[1024];
	snprintf(path, sizeof(path), "../../%s", filename);
	return path;
}

/**
 * is_executable - Vérifie si un fichier est exécutable.
 *
 * @path: Le chemin du fichier à vérifier.
 *
 * Description:
 * Cette fonction utilise la fonction `stat` pour vérifier si le fichier
 * spécifié par `path` existe et s'il est exécutable par l'utilisateur.
 *
 * Return:
 * Retourne 1 si le fichier est exécutable, sinon 0.
 */
/* Fonction pour vérifier si un fichier est exécutable */
int is_executable(const char *path)
/*{*/
/*struct stat st;*/

/* Vérifie si le fichier existe et est exécutable */
/*if (stat(path, &st) == 0 && (st.st_mode & S_IXUSR))*/
/*{*/
/*	return (1);  Le fichier est exécutable */
/*}*/
/*return (0);  Le fichier n'est pas exécutable */
/*}*/
{
	return access(path, X_OK) == 0;
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
	char *cwd;
	char *path1 = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"; /*Example PATH*/
	char *path_copy;
	char *token;

	/* Obtenez le répertoire de travail actuel */
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (NULL);
	}

	/* Construisez le chemin complet pour la commande dans le répertoire actuel */
	snprintf(full_path, sizeof(full_path), "%s/%s", cwd, cmd);
	/*printf("Checking in current directory: %s\n", full_path);*/

	/* Vérifiez si le fichier est exécutable dans le répertoire courant */
	if (is_executable(full_path))
	{
		free(cwd);
		return strdup(full_path); /* Retourne le chemin complet du fichier */
	}

	free(cwd);

	/* Utilisation d'un PATH simulé */
	path_copy = strdup(path1);
	/*path_copy = strdup(PATH1);*/
	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}

	/* Découpez PATH simulé en répertoires */
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		/* Construisez le chemin complet pour la commande dans chaque répertoire de PATH */
		snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
		/*printf("Checking in PATH directory: %s\n", full_path);*/

		/* Vérifiez si la commande existe et est exécutable */
		if (is_executable(full_path))
		{
			free(path_copy);
			return strdup(full_path); /* Retourne le chemin complet du fichier */
		}
		token = strtok(NULL, ":");
		/*token = strtok(NULL, &PATH1_DELIM);*/
	}

	free(path_copy);
	return (NULL); /* Retourne NULL si la commande n'est pas trouvée */
}
