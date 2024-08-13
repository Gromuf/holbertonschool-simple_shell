#include "main.h"

/**
 * _isspace - Checks if a character is a whitespace character.
 *
 * @c: The character to be checked.
 *
 * Return: 1 if the character is a whitespace character, 0 otherwise.
 */
int _isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r');
}
