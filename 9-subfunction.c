#include "main.h"

/**
 * display_prompt - Displays the command prompt.
 *
 * This function prints the prompt character '$ ' to the standard output
 * and ensures that it is immediately visible by flushing the output buffer.
 */
void display_prompt(void)
{
	printf(":) ");
	fflush(stdout);
}

/**
 * is_interactive - Checks if the shell is running in interactive mode.
 *
 * Return: 1 if the shell is interactive, 0 otherwise.
 */
int is_interactive(void)
{
	return (isatty(STDIN_FILENO));
}

/**
 * _isspace - Checks if a character is a whitespace character.
 *
 * @c: The character to be checked.
 *
 * Return: 1 if the character is a whitespace character, 0 otherwise.
 */
int _isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' ||
		c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

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

	cmd[_strcspn(cmd, "\n")] = 0;
	return (cmd);
}
