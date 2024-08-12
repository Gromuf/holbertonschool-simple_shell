#include "main.h"

/**
 * main - Point d'entrée du programme shell simple.
 *
 * Cette fonction exécute une boucle infinie qui affiche un prompt,
 * lit une commande entrée par l'utilisateur, puis exécute cette
 * commande. La boucle se termine si une entrée EOF est détectée.
 *
 * Retourne: Toujours 0 (succès).
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

		printf("%s\n", cmd);

		exec_cmd(cmd);
		free(cmd);
	}
	return (0);
}
