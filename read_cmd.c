#include "main.h"

/**
 * read_cmd - Reads a command from standard input.
 *
 * This function reads a line of input from the user using getline().
 * If the input is successfully read, it removes the newline character
 * and returns the command. If an error occurs or EOF is detected,
 * it frees the allocated memory and returns NULL.
 *
 * Return: A pointer to the command string, or NULL on failure.
 */
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

	cmd[_strcspn(cmd, "\n")] = 0;
	return (cmd);
}

/**
 * execute_command - Execute a shell command.
 * @command: The command to be executed.
 *
 * This function takes a command string as input and executes it. If the
 * command is "exit", the shell will terminate. For other commands, it
 * will currently print a "Command not found" message. The actual execution
 * of commands other than "exit" should be implemented as needed.
 *
 * Return: None
 *
 * Description:
 * The function compares the provided command with the string "exit". If
 * they match, it prints a message indicating the shell is exiting and
 * then calls `exit(EXIT_SUCCESS)` to terminate the shell. If the command
 * does not match "exit", it prints a message indicating that the command
 * is not found. This function currently does not handle other commands.
 */
void execute_command(const char *cmd)
{
	if (strcmp(cmd, "exit") == 0)
	{
		/*Quitter le shell*/
		printf("Exiting shell...\n");
		exit(EXIT_SUCCESS);
	}
	printf("Command not found: %s\n", cmd);
}
