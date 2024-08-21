#include "main.h"

/**
 * my_strtok - Simule la fonction strtok.
 * @str: La chaîne à découper.
 * @delim: La chaîne des délimiteurs.
 *
 * Return: Le prochain token ou NULL si aucun token n'est trouvé.
 */
char *my_strtok(char *str, const char *delim)
{
	static char *saveptr;

	return (_strtok_r(str, delim, &saveptr));
}
