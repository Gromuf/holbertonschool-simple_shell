#include "main.h"

/**
 * display_prompt - Displays the command prompt.
 *
 * This function prints the prompt character '$ ' to the standard output
 * and ensures that it is immediately visible by flushing the output buffer.
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO)) /*add dans use pipe*/
	{
		printf("#cisfun$ ");
		fflush(stdout);
	}
}
