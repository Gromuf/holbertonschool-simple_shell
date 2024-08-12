#include "main.h"

int main(void)
{
	char *cmd = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("$ "); // Print the prompt

		read = getline(&cmd, &len, stdin); // Read the user input
		if (read == -1)
		{		   // Check for EOF or error
			break; // Exit the loop if end-of-file is encountered
		}

		printf("%s", line); // Print the command back to the user
		command[strcspn(command, "\n")] = 0;

		pid_t pid = fork();
		if (pid == 0)
		{
			// Child process
			char *argv[] = {command, NULL}; // Command without arguments
			if (execve(command, argv, NULL) == -1)
			{
				perror("Error");
			}
			exit(EXIT_FAILURE); // Exit child process if execve fails
		}
	}

	free(command);
	return (0);
}