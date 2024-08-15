#include "main.h"
#include <stdio.h>
#include <stdlib.h>

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
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	/* Display the prompt */
	/*printf("#cisfun$ ");*/
	/*fflush(stdout);*/

	/* Read a line of input */
	read = getline(&line, &len, stdin);

	/* Check for errors or EOF */
	if (read == -1)
	{
		if (feof(stdin)) /* End of file (Ctrl+D) */
		{
			free(line);
			return NULL; /* Return NULL to indicate end of input */
		}
		else if (ferror(stdin)) /* Check for read error */
		{
			perror("getline");
			free(line);
			return NULL; /* Return NULL on error */
		}
	}

	if (feof(stdin))
	{
		free(line);
		_exit(EXIT_SUCCESS);
	}
	else if (ferror(stdin))
	{
		perror("getline");
		free(line);
		return (NULL);
	}

	/* Remove the newline character, if present */
	if (read > 0 && line[read - 1] == '\n')
	{
		line[read - 1] = '\0';
	}

	return (line);
}
