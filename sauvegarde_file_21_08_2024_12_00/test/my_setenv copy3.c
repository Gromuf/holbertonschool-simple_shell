/* my_setenv.c */
#include "main.h"
#include <stdlib.h>
#include <string.h>

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
	char *new_env_var;
	size_t name_len;
	size_t value_len;

	/* Vérification si le nom ou la valeur est NULL */
	if (name == NULL || value == NULL)
	{
		perror("my_setenv: name or value is NULL");
		return (-1);
	}

	/* Vérifier si la variable existe déjà et si on ne souhaite pas écraser */
	if (getenv(name) != NULL && !overwrite)
	{
		return (0); /* Variable d'environnement déjà définie et non écrasée */
	}

	/* Calcul des longueurs */
	name_len = strlen(name);
	value_len = strlen(value);

	/* Allocation de mémoire pour la nouvelle variable d'environnement */
	new_env_var = malloc(name_len + value_len + 2); /* +2 pour '=' et '\0' */
	if (new_env_var == NULL)
	{
		perror("my_setenv: malloc failed");
		return (-1);
	}

	/* Construction de la chaîne de la variable d'environnement */
	strcpy(new_env_var, name);
	strcat(new_env_var, "=");
	strcat(new_env_var, value);

	/* Définition de la variable d'environnement */
	if (putenv(new_env_var) != 0)
	{
		perror("my_setenv: putenv failed");
		free(new_env_var); /* Nettoyer la mémoire en cas d'échec */
		return (-1);
	}

	/* Note: Ne pas libérer new_env_var car putenv() l'utilise */
	return (0);
}
