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
	ssize_t read;

	read = getline(&cmd, &len, stdin);
	if (read == -1)
	{
		free(cmd);
		return (NULL);
	}

	/*cmd[strcspn(cmd, "\n")] = 0;*/

	/* Remove newline character */
	if (cmd[read - 1] == '\n') /*Check if the last character is newline*/
	{
		cmd[read - 1] = '\0'; /*Replace it with null terminator*/
	}

	return (cmd);
}
