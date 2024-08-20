#include "main.h"
#include <stdlib.h> /* for malloc */
#include <string.h> /* for strlen */

/**
 * _strdup - Duplicates a string.
 * @s: The string to be duplicated.
 *
 * Return: A pointer to the duplicated string, or NULL if memory allocation
 *         fails.
 */
char *_strdup(const char *s)
{
	char *duplicate;
	size_t len = strlen(s) + 1; /* Include space for the null terminator */

	duplicate = (char *)malloc(len);
	if (duplicate == NULL)
		return NULL;

	memcpy(duplicate, s, len);
	return (duplicate);
}
