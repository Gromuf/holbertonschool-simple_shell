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
	/*char *cmd = NULL;*/
	char *cmd = NULL;
	size_t len = 0;
	ssize_t read; /*Utilisez ssize_t pour la valeur de retour de getline*/

	/*Lit une ligne d'entrée*/
	read = getline(&cmd, &len, stdin);

	/*Si getline échoue ou si l'utilisateur appuie sur EOF (Ctrl+D)*/
	if (read == -1)
	{
		free(cmd);
		return (NULL);
	}

	cmd[_strcspn(cmd, "\n")] = '\0';

	return (cmd);

}
