#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PATH_DELIM ':'

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
{
	struct stat st;

	/* Vérifie si le fichier existe et est exécutable */
	if (stat(path, &st) == 0 && (st.st_mode & S_IXUSR))
	{
		return (1); /* Le fichier est exécutable */
	}
	return (0); /* Le fichier n'est pas exécutable */
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
	extern char **environ;  /* Déclaration de la variable globale environ*/
	char *path;
	char *token;
	char *path_copy;
	char full_path[1024];
	char **env;

	/*path = getenv("PATH");*/

	/* Cherche la variable PATH dans environ*/
	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
		{
			path = *env + 5;  /* Obtenir le chemin après "PATH="*/
			break;
		}
	}

	if (path == NULL)
		return (NULL); /*Retourne NULL si PATH n'est pas défini*/

	/*token = strtok(path, ":");*/
	/*while (token != NULL)*/
	/*{*/
	/* Duplicate the PATH environment variable */
	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		 /* Construct the full path to the command */
		snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);

		/* Check if the command exists and is executable */
		if (access(full_path, X_OK) == 0)
			{
				free(path_copy);
				return (strdup(full_path)); /*Return the full path of the cmd*/
			}
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL); /* Return NULL if the command is not found */
}
