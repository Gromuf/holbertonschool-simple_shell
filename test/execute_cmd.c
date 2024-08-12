#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/**
 * execute_cmd - Executes a command.
 * @cmd: The command to execute.
 *
 * Return: 0 on success, -1 on failure.
 */
int execute_cmd(char *cmd)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return -1;
	}

	if (pid == 0)
	{
		// Enfant
		execlp(cmd, cmd, (char *)NULL);
		// Si execlp échoue
		fprintf(stderr, "./shell: %s: %s\n", cmd, strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		// Parent
		int status;
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			fprintf(stderr, "./shell: %s: No such file or directory\n", cmd);
		}
	}
	return 0;
}
