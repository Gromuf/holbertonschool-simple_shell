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
	int exit_status = 0;

	while (1)
	{
		if (is_interactive())
			display_prompt();

		cmd = read_cmd();
		if (cmd == NULL) /* Handle end of file (Ctrl+D) or read error */
			break;

		if (_strcmp(cmd, "env") == 0)
		{
			print_env();
			free(cmd);
			continue;
		}
/*else if (_strcmp(cmd, "exit") == 0 || (strlen(cmd) == 1 && cmd[0] == 3))*/
		else if (strncmp(cmd, "exit", 4) == 0)
		{
			exit_status = parse_exit_status(cmd);
			free(cmd); /*free memory before quit */
			break;
		}

		exec_multiple_cmd(cmd);
		free(cmd);
	}

	return (exit_status);
}
