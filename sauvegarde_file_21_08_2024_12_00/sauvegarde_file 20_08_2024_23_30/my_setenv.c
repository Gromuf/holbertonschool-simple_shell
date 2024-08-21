/* my_setenv.c */
#include "main.h"
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * my_setenv - Sets or modifies an environment variable.
 *
 * @name: The name of the environment variable.
 * @value: The value to set the environment variable to.
 * @overwrite: If non-zero, overwrite an existing variable;
 *             if zero, do not overwrite.
 *
 * Return: 0 on success, -1 on error.
 *
 * Description: This function sets or modifies an environment variable.
 * If the environment variable specified by 'name' already exists and
 * 'overwrite' is non-zero, the variable is updated to hold the new 'value'.
 * If 'overwrite' is zero and the variable already exists, the value remains
 * unchanged. The function returns -1 if an error occurs, otherwise 0 on
 * success. Memory for the new environment variable is dynamically allocated
 * and should not be freed, as it is managed by the system's environment
 * variable handling.
 */
int my_setenv(const char *name, const char *value, int overwrite)
{
	size_t name_len;
	size_t value_len;
	size_t new_size;
	char *new_env_var;
	char **new_environ;
	int i;

	if (name == NULL || value == NULL)
		return (-1);

	name_len = strlen(name);
	value_len = strlen(value);
	new_size = name_len + value_len + 2; /* +2 for '=' and '\0' */

	new_env_var = malloc(new_size);
	if (new_env_var == NULL)
	{
		perror("malloc");
		return (-1);
	}

	/* Create the new string for the environment variable */
	snprintf(new_env_var, new_size, "%s=%s", name, value);

	/* Check if the variable already exists and handle it */
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			if (overwrite)
			{
				/* Replace the existing variable */
				free(environ[i]);
				environ[i] = new_env_var;
				return (0);
			}
			free(new_env_var); /*Free if not overwriting*/
			return (0);
		}
	}

	/* Variable not found, so add it */
	new_environ = realloc(environ, (i + 2) * sizeof(char *));
	if (new_environ == NULL)
	{
		perror("realloc");
		free(new_env_var);
		return (-1);
	}

	environ = new_environ;
	environ[i] = new_env_var;
	environ[i + 1] = NULL;

	return (0);
}
