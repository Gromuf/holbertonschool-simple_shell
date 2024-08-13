#include "main.h"

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