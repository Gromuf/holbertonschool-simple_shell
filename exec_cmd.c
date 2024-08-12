#include "main.h"

void exec_cmd(char *cmd)
{
	pid_t pid;
	char *argv[2];

	pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		return;
	}

	if (pid == 0)
	{
		argv[0] = cmd;
		argv[1] = NULL;
		if (execve(cmd, argv, NULL) == -1)
		{
			perror("Error");
		}
		exit(EXIT_FAILURE);
	}

	else
		wait(NULL);
}
