#include "main.h"
/**
 * _strlen - Computes the length of a string.
 * @s: The string whose length is to be computed.
 *
 * Return: The length of the string.
 */
size_t _strlen(const char *s)
{
	const char *p = s;

	while (*p)
		p++;

	return (p - s);
}
