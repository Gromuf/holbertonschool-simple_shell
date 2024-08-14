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
		return 1; /* Le fichier est exécutable */
	}
	return 0; /* Le fichier n'est pas exécutable */
}

/**
 * which - Recherche le chemin complet d'un fichier exécutable dans PATH.
 *
 * @filename: Le nom du fichier à rechercher.
 *
 * Description:
 * Cette fonction recherche le fichier spécifié par `filename` dans les
 * répertoires listés dans la variable d'environnement `PATH`. Elle construit
 * le chemin complet pour chaque répertoire et vérifie si le fichier est
 * exécutable en utilisant la fonction `is_executable`.
 *
 * Return:
 * Retourne un pointeur vers une chaîne de caractères contenant le chemin
 * complet du fichier si trouvé, sinon retourne NULL.
 * La chaîne de caractères allouée dynamiquement doit être libérée par
 * l'appelant.
 */
/* Fonction qui imite le comportement de 'which' */
char *which(const char *filename)
{
	char *path_env;
	char *path_copy;
	char *dir;
	char full_path[1024]; /* Taille maximale du chemin complet */
	/*FILE *file;*/
	long unsigned int path_len;

	/* Récupère la variable d'environnement PATH */
	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		return (NULL); /* La variable d'environnement PATH n'est pas définie */
	}

	/* Crée une copie de la variable PATH pour la manipulation */
	path_copy = strdup(path_env);
	if (path_copy == NULL)
	{
		return (NULL); /* Erreur d'allocation mémoire */
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		/* Construit le chemin complet vers le fichier */
		path_len = snprintf(full_path, sizeof(full_path), "%s/%s", dir, filename);
		if (path_len >= sizeof(full_path))
		{
			/* Chemin trop long, passe au répertoire suivant */
			dir = strtok(NULL, ":");
			continue;
		}

		/* Vérifie si le fichier est exécutable */
		if (is_executable(full_path))
		{
			/* Alloue et copie le chemin complet vers une nouvelle chaîne */
			char *result = strdup(full_path);
			free(path_copy);
			return (result);
		}

		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL); /* Fichier non trouvé dans PATH */
}
