#include "main.h"

/**
 * _strchr - Locates the first occurrence of a character in a string.
 * @s: The string to be searched.
 * @c: The character to be located.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: An integer less than, equal to, or greater than zero, depending
 *         on whether the first string is less than, equal to, or greater
 *         than the second string.
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

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
size_t _strcspn(const char *s1, const char *s2)
{
	size_t i;
	size_t j;

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
		return (NULL);

	memcpy(duplicate, s, len);
	return (duplicate);
}

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
