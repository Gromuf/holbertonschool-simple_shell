#include "main.h"
#include <stddef.h>
#include <string.h>

/**
 * _strtok_r - Custom implementation of strtok_r
 * @str: The string to be tokenized, or NULL to continue tokenizing
 * @delim: The delimiters used to tokenize the string
 * @saveptr: Pointer to a char* variable that stores the state between calls
 *
 * Return: A pointer to the next token, or NULL if no more tokens are found
 */
char *_strtok_r(char *str, const char *delim, char **saveptr)
{
	char *start; /* Start of the next token */
	char *end;	 /* End of the current token */

	if (str == NULL)
	{
		str = *saveptr;
	}

	/* Skip leading delimiters */
	start = str;
	while (*start && strchr(delim, *start))
	{
		start++;
	}

	if (*start == '\0')
	{
		/* No more tokens */
		*saveptr = start;
		return (NULL);
	}

	/* Find the end of the token */
	end = start;
	while (*end && !strchr(delim, *end))
	{
		end++;
	}

	if (*end)
	{
		*end = '\0';		/* Null-terminate the current token */
		*saveptr = end + 1; /* Save the state for the next call */
	}
	else
	{
		*saveptr = end; /* No more tokens */
	}

	return (start);
}

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
