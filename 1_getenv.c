#include "main.h"
#include <stddef.h> /* for NULL */
#include <string.h> /* for strcmp */

/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable to retrieve.
 *
 * Return: The value of the environment variable, or NULL if the variable
 *         is not found.
 */
char *_getenv(const char *name)
{
	/*extern char **environ;  Access the environment variables */
	char **env = environ;
	size_t name_len = strlen(name);
	char *equals;

	while (*env)
	{
		/* Find the '=' character in the environment string */
		equals = strchr(*env, '=');
		if (equals != NULL)
		{
			/* Compare the variable name with the part before '=' */
			if ((size_t)(equals - *env) == name_len &&
				strncmp(*env, name, name_len) == 0)
			{
				/* Return the value (after '=') */
				return (equals + 1);
			}
		}
		env++;
	}

	return (NULL); /* Variable not found */
}
