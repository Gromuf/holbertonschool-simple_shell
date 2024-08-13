#include "main.h"

int should_exit = 0; /*Variable globale pour contrôler la sortie du shell*/

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
	/*char input[1024];*/

	/*while (1)*/
	while (!should_exit) /*utiliser should_exit pour contrôler la boucle*/
	{
		if (is_interactive())
			display_prompt();

		cmd = read_cmd();
		if (cmd == NULL)
			break;

		exec_multiple_cmd(cmd);
		free(cmd);
	}

	/*printf("Exiting shell\n");*/
	/*Retourner un code de sortie approprié, selon les besoins*/
	/* code 0 pour exit et 2 pour /bin/ls: cannot*/
	/* access '/test_hbtn': No such file or directory*/
	return (should_exit ? 0 : 2);

	/*return (0);*/
}
