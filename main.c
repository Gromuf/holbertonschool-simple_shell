#include "main.h"

/**
 * main - Entry point of the simple shell program.
 *
 * This function runs an infinite loop that displays a prompt,
 * reads a command input by the user, executes the command,
 * and handles end-of-file (EOF) conditions. The loop terminates
 * when an EOF is detected (e.g., via Ctrl+D).
 *
 * Return: Always 0 (success).
 */
int main(void)
{
	char *cmd = NULL;

	while (1)
	{
		display_prompt();

		cmd = read_cmd();
		if (cmd == NULL)
			break;

		exec_cmd(cmd);
		free(cmd);
	}
	return (0);
}
