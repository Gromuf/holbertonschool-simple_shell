#include "main.h"

/**
 * read_cmd - Lit une commande entrée par l'utilisateur.
 *
 * Cette fonction utilise getline pour lire une ligne de l'entrée standard
 * et renvoie la commande lue. Si une erreur se produit ou si EOF est
 * détecté, elle libère la mémoire allouée et retourne NULL.
 *
 * Retourne: Un pointeur vers la commande lue, ou NULL en cas d'erreur.
 */
char *read_cmd(void)
{
	char *cmd = NULL;
	size_t len = 0;
	ssize_t read;

	read = getline(&cmd, &len, stdin);
	if (read == -1)
	{
		free(cmd);
		return (NULL);
	}

	cmd[strcspn(cmd, "\n")] = 0;
	return (cmd);
}
