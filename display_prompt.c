#include "main.h"

/**
 * display_prompt - Affiche le prompt de commande.
 *
 * Cette fonction affiche un prompt "$ " et force l'affichage immédiat
 * à l'écran en vidant le tampon de sortie standard.
 */
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
