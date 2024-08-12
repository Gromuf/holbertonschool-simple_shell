#include "main.h"

int main(void)
{
	char *cmd = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;
	char *argv[2];

	while (1)
	{
		printf("$ ");

		read = getline(&cmd, &len, stdin);
		if (read == -1)
		{
			break;
		}

		printf("%s", cmd);
		cmd[strcspn(cmd, "\n")] = 0;

		pid = fork();
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
	}

	free(cmd);
	return (0);
}