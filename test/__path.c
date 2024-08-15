#include "main.h"

#define BUFFER_SIZE 1024

char *find_command_path(const char *cmd)
{
	char *path_env = getenv("PATH");
	char *path;

	/*if (path_env == NULL)*/
	/*{*/
	/*	path_env = "/bin:/usr/bin";  Default path*/
	/*}*/

	path = strtok(path_env, ":");
	while (path != NULL)
	{
		char full_path[BUFFER_SIZE];
		snprintf(full_path, sizeof(full_path), "%s/%s", path, cmd);

		if (access(full_path, X_OK) == 0)
		{
			char *result = malloc(strlen(full_path) + 1);
			if (result != NULL)
			{
				strcpy(result, full_path);
				return (result);
			}
		}

		path = strtok(NULL, ":");
	}

	return (NULL);
}
