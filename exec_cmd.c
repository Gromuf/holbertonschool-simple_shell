#include "main.h"

/**
 * exec_cmd - Executes a command in a new process.
 *
 * @cmd: The command to be executed.
 *
 * This function creates a new process using fork(). If the fork is
 * successful, the child process attempts to execute the specified command
 * using execve(). If execve() fails, an error message is printed.
 * The parent process waits for the child process to finish execution.
 */
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
			/*perror("Error");*/
		}
		/*ajout SD ./shell: No such file or directory*/
		/*fprintf(stderr, "./shell: %s: %s\n", cmd, strerror(errno));*/
		fprintf(stderr, "./shell: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	else
		wait(NULL);
}
