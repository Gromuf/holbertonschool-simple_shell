#include "main.h"
#include <stddef.h>
#include <string.h>

/**
 * my_strtok - Simule la fonction strtok.
 * @str: La chaîne à découper.
 * @delim: La chaîne des délimiteurs.
 *
 * Return: Le prochain token ou NULL si aucun token n'est trouvé.
 */
char *my_strtok(char *str, const char *delim)
{
	char *start;
	static char *next_token = NULL; /* Variable statique pour maintenir l'état entre les appels */

	/* Si str est NULL, utilisez la chaîne précédente enregistrée */
	if (str == NULL)
	{
		str = next_token;
	}

	/* Si str est NULL ou vide, retournez NULL */
	if (str == NULL || *str == '\0')
	{
		return (NULL);
	}

	/* Avancez le début de la chaîne jusqu'au premier caractère non délimiteur */
	str += strspn(str, delim);
	if (*str == '\0') /* Si toute la chaîne était constituée de délimiteurs */
	{
		next_token = NULL;
		return (NULL);
	}

	/* Enregistrez le début du token */
	start = str;

	/* Trouvez le prochain délimiteur */
	str = strpbrk(start, delim);
	if (str == NULL)
	{
		/* Aucun délimiteur trouvé, fin de la chaîne */
		next_token = NULL;
	}
	else
	{
		/* Remplacez le délimiteur par '\0' et avancez le pointeur */
		*str = '\0';
		next_token = str + 1;
	}

	return (start);
}
