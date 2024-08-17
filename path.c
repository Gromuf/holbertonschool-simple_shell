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
 * @cmd: Le nom du fichier à rechercher.
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
char *which(char *cmd)
{
	char *path = getenv("PATH");
	char *token;
	char full_path[1024];

	if (path == NULL)
		return NULL;

	token = strtok(path, ":");
	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, cmd);
		if (access(full_path, X_OK) == 0)
			return strdup(full_path);
		token = strtok(NULL, ":");
	}

	return NULL;
}
