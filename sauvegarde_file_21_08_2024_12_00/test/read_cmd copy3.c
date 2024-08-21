#include "main.h"

/**
 * read_cmd - Reads a command from standard input.
 *
 * This function reads a line of input from the user using getline().
 * If the input is successfully read, it removes the newline character
 * and returns the command. If an error occurs or EOF is detected,
 * it frees the allocated memory and returns NULL.
 *
 * Return: A pointer to the command string, or NULL on failure.
 */
char *read_cmd(void)
{
	char *cmd = NULL;
	size_t len = 0;
	ssize_t read; /*Utilisez ssize_t pour la valeur de retour de getline*/

	/*Affiche le prompt*/
	/*printf("#cisfun$ ");*/
	/*fflush(stdout);*/

	/*Lit une ligne d'entrée*/
	read = getline(&cmd, &len, stdin);

	/*Si getline échoue ou si l'utilisateur appuie sur EOF (Ctrl+D)*/
	if (read == -1)
	{
		/* Handle end-of-file (EOF) or other errors */
		/*if (cmd == NULL)*/
		/*{*/
			/* If cmd is NULL, there was an error, so return NULL */
			/*return NULL;*/
		/*}*/

		/* If EOF or other error, free cmd and return NULL */
		free(cmd);
		return (NULL);
	}
	/*perror("getline");*/
	/*free(cmd);*/
	/*continue;*/

	/* Supprime le caractère de nouvelle ligne, si présent */
	/*cmd[_strcspn(cmd, "\n")] = 0;*/

	/*Supprime le caractère de nouvelle ligne, si présent*/
	/*if (line[read - 1] == '\n')*/
	/*{*/
	/*line[read - 1] = '\0';*/
	/*}*/

	/* Supprime le caractère de nouvelle ligne, si présent */
	if (read > 0 && cmd[read - 1] == '\n')
	{
		cmd[read - 1] = '\0';
	}
	/*else*/
		/*free (cmd);*/

	/*free (cmd);*/
	/*free (cmd);*/
	/*free (len);*/

	return (cmd);
}

/*char *read_cmd(void)*/
/*{*/
/*char *cmd = NULL;*/
/*size_t len = 0;*/
/*ssize_t read;*/

/*read = getline(&cmd, &len, stdin);*/
/*if (read == -1)*/
/*{*/
/*	free(cmd);*/
/*	return (NULL);*/
/*}*/

/*cmd[_strcspn(cmd, "\n")] = 0;*/
/*return (cmd);*/
/*}*/
