#include "main.h"

/**
 * exec_multiple_cmd - Executes multiple commands from a string.
 * @cmd: The string containing commands separated by newlines.
 *
 * This function splits the input string into individual commands
 * and executes each command using exec_cmd. Each command is
 * processed in a separate child process.
 */
void exec_multiple_cmd(char *cmd)
{
	char *line;
	const char delim[2] = "\n";
	char *saveptr;

	line = _strtok_r(cmd, delim, &saveptr);

	while (line != NULL)
	{
		if (!is_empty_cmd(line))
			exec_cmd(line);
		line = _strtok_r(NULL, delim, &saveptr);
	}
}
