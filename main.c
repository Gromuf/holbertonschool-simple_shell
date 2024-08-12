#include "main.h"

int main(void)
{
	char *cmd = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("$ ");

		read = getline(&cmd, &len, stdin);
		if (read == -1)
		{
			break;
		}

		printf("%s", read);
		cmd[strcspn(cmd, "\n")] = 0;

		pid_t pid = fork();
		if (pid == 0)
		{
			char *argv[] = {command, NULL};
			if (execve(command, argv, NULL) == -1)
			{
				perror("Error");
			}
			exit(EXIT_FAILURE);
		}
	}

	free(command);
	return (0);
}