#include "main.h"

/**
 * _strcspn - Calculates the length of the initial segment of s1
 *            which consists of characters not in s2.
 *
 * @s1: The string to be searched.
 * @s2: The string containing the characters to exclude.
 *
 * Return: The length of the initial segment of s1 not containing
 *         any characters from s2.
 */
long unsigned int _strcspn(const char *s1, const char *s2)
{
	long unsigned int i;
	long unsigned int j;

	for (i = 0; s1[i] != '\0'; i++)
	{
		for (j = 0; s2[j] != '\0'; j++)
		{
			if (s1[i] == s2[j])
				return (i);
		}
	}

	return (i);
}
