#include "main.h"

char *read_cmd(void)
{
	char *cmd = NULL;
	size_t len = 0;
	ssize_t read;

	read = getline(&cmd, &len, stdin);
	if (read == -1)
	{
		free(cmd);
		return (NULL);
	}

	cmd[strcspn(cmd, "\n")] = 0;
	return (cmd);
}
