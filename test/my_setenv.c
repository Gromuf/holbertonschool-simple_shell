/* my_setenv.c */
#include "main.h"
#include <string.h>
#include <stdlib.h>

extern char **environ;

int my_setenv(const char *name, const char *value, int overwrite)
{
	char **env;
	size_t name_len;
	size_t value_len;
	size_t new_size;
	char *new_env_var;
	char **new_environ;
	/*int i;*/

	name_len = strlen(name);
	value_len = strlen(value);
	new_size = name_len + value_len + 2; /* +2 pour '=' et '\0' */

	new_env_var = (char *)malloc(new_size);
	if (new_env_var == NULL)
	{
		perror("malloc");
		return (-1);
	}

	/* Créer la nouvelle chaîne pour la variable d'environnement */
	snprintf(new_env_var, new_size, "%s=%s", name, value);

	env = environ;
	while (*env)
	{
		if (strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			if (overwrite)
			{
				/* Remplacer la variable existante */
				free(*env);
				*env = new_env_var;
				return (0);
			}
			free(new_env_var);
			return (0); /* Ne rien faire si non remplacement */
		}
		env++;
	}

	/* Si nous arrivons ici, la variable n'a pas été trouvée, donc nous l'ajoutons */
	new_environ = (char **)realloc(environ, (env - environ + 2) * sizeof(char *));
	if (new_environ == NULL)
	{
		perror("realloc");
		free(new_env_var);
		return (-1);
	}

	environ = new_environ;
	environ[env - environ] = new_env_var;
	environ[env - environ + 1] = NULL;

	return (0);
}
