#include "main.h"

/*int should_exit = 0; Variable globale pour contrôler la sortie du shell*/

void set_PATH1(void)
{
	/* Assigner la valeur par défaut au PATH*/
	if (my_setenv("PATH", PATH1, 1) != 0)
	{
		perror("my_setenv");
		exit(EXIT_FAILURE);
	}
}

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

	/*Initialiser PATH avec la valeur par défaut*/
	/*set_PATH1();*/

	/*char input[1024];*/
	/*char command1[] = "./hbtn_ls /var";  Cas où on exécute un chemin relatif */
	/*char command2[] = "ls";              Cas où PATH est vide */

	while (1)
	/*while (!should_exit) utiliser should_exit pour contrôler la boucle*/
	{
		if (is_interactive())
			display_prompt();

		cmd = read_cmd();
		if (cmd == NULL)
			break;

		/*exec_cmd(command1);*/
		/*exec_cmd(command2);*/

		if (strcmp(cmd, "exit") == 0 || (strlen(cmd) == 1 && cmd[0] == 3)) /*Gérer la commande "exit" */
		{ /*3 est le code ASCII pour Ctrl+C*/
			free(cmd); /*Libérer la mémoire avant de quitter */
			/*should_exit = 1;*/
			break;
		}

		/*Afficher le PATH pour vérifier*/
		/*printf("PATH: %s\n", _getenv("PATH"));*/

		exec_multiple_cmd(cmd);
		free(cmd);
	}

	/* Affiche un message ou non, selon les besoins */
	/*printf("Exiting shell with code %d\n", should_exit);*/

	/*printf("Exiting shell\n");*/
	/*Retourner un code de sortie approprié, selon les besoins*/
	/* code 0 pour exit et 2 pour /bin/ls: cannot*/
	/* access '/test_hbtn': No such file or directory*/
	/*return (should_exit ? 2 : 0);*/
	/*return (should_exit);*/

	return (0); /* Sortir avec code 0 lorsque le shell se termine */
}
