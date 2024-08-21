#include "main.h"
#include <stddef.h> /* for NULL */
#include <string.h> /* for strcmp */

/**
 * _getenv - Retrieves the value of an environment variable from envp.
 * @name: The name of the environment variable.
 * @envp: Array of environment variables.
 *
 * Description: This function retrieves the value of an environment variable
 * from the envp array. It returns a pointer to the value of the environment
 * variable if found, or NULL if the variable does not exist.
 *
 * Return: A pointer to the value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name, char **envp)
{
	size_t name_len = strlen(name);
	char *env_entry;
	char *value;

	while ((env_entry = *envp++) != NULL)
	{
		/* Check if the current env_entry starts with the name followed by '=' */
		if (strncmp(env_entry, name, name_len) == 0 && env_entry[name_len] == '=')
		{
			/* Skip the name and '=' to get to the value */
			value = env_entry + name_len + 1;
			return strdup(value);
		}
	}

	/* Return NULL if the environment variable is not found */
	return NULL;
}
