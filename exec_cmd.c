#include "main.h"

/**
 * is_empty_cmd - Checks if a command string is empty or contains only
 * whitespace.
 *
 * @cmd: A pointer to the command string to be checked.
 *
 * Return: 1 if the command is empty or contains only whitespace,
 *         0 otherwise.
 */
int is_empty_cmd(char *cmd)
{
	while (*cmd)
	{
		if (_isspace((unsigned char)*cmd) == 0)
			return (0);
		cmd++;
	}
	return (1);
}
/**
 * exec_cmd - Executes a command in a new process.
 * @cmd: The command to be executed.
 *
 * This function creates a new process using fork(). If the fork is
 * successful, the child process attempts to execute the specified
 * command using execve(). If execve() fails, an error message is
 * printed. The parent process waits for the child process to finish
 * execution.
 */
void exec_cmd(char *cmd)
{
	pid_t pid;
	char *argv[100];
	char *token;
	int i = 0;

	if (is_empty_cmd(cmd))
		return;

	token = strtok(cmd, " \n");
	while (token != NULL)
	{
		argv[i++] = token;
		token = strtok(NULL, " \n");
	}
	argv[i] = NULL;

	pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		return;
	}

	if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			/*perror("Error");*/
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}

/**
 * exec_multiple_cmd - Executes multiple commands from a string.
 * @cmds: The string containing commands separated by newlines.
 *
 * This function splits the input string into individual commands
 * and executes each command using exec_cmd. Each command is
 * processed in a separate child process.
 */
void exec_multiple_cmd(char *cmds)
{
	char *line;
	const char delim[2] = "\n";
	line = strtok(cmds, delim);

	while (line != NULL)
	{
		exec_cmd(line);
		line = strtok(NULL, delim);
	}
}
