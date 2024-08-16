#include "main.h"

int should_exit = 0; /*Variable globale pour contrôler la sortie du shell*/

/*#define BUFFER_SIZE 1024*/

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
	char *cmd;

	/*const char *path = getenv("PATH");*/
	/*char input[1024];*/

	/*if (setenv("PATH",*/
	/*"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 1) == -1)*/

	/*if (setenv("PATH", "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", 1) == -1)*/
	/*{*/
	/*	perror("setenv");*/
	/*	return (EXIT_FAILURE);*/
	/*}*/

	/*while (1)*/
	while (!should_exit) /*utiliser should_exit pour contrôler la boucle*/
	{
		if (is_interactive())
			display_prompt();

		cmd = read_cmd();
		if (cmd== NULL)
		{
			/*free(cmd);*/
			break;
		}

		/*exec_cmd(cmd);*/
		exec_multiple_cmd(cmd);
		free(cmd);
	}
	/*free(cmd);*/

	/* Affiche un message ou non, selon les besoins */
	/*printf("Exiting shell with code %d\n", should_exit);*/

	/*printf("Exiting shell\n");*/
	/*Retourner un code de sortie approprié, selon les besoins*/
	/* code 0 pour exit et 2 pour /bin/ls: cannot*/
	/* access '/test_hbtn': No such file or directory*/
	/*return (should_exit ? 2 : 0);*/
	/*return (should_exit);*/

	/*return (0);  Sortir avec code 0 lorsque le shell se termine */

	/* Afficher OK à la fin si tout s'est bien passé */
	/*printf("OK");*/
	/*free (cmd); cette commande provoque segmentation fault*/

	/*return (should_exit ? 2 : 0);*/
	return (0);
}
