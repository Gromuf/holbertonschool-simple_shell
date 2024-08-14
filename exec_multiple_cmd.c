#include "main.h"
#include <stdio.h>
#include <stdlib.h>   /* Pour NULL*/

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
