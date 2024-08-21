#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * exec_cmd - Executes a command.
 * @cmd: The command to execute.
 */
void exec_cmd(char *cmd)
{
	char *cmd_path = find_command_path(cmd);
	pid_t pid;

	if (cmd_path == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", cmd);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(cmd_path);
		return;
	}

	if (pid == 0)
	{
		/* Child process */
		execl(cmd_path, cmd, (char *)NULL);
		perror("execl"); /*execl only returns on error*/
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent process */
		int status;
		waitpid(pid, &status, 0);
	}

	free(cmd_path); /* Free the allocated memory for the command path*/
}
