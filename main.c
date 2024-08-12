#include "main.h"

int main(void)
{
	while (1)
	{
		display_prompt();

		cmd = read_cmd();
		if (cmd == NULL)
			break;

		printf("%s", cmd);

		exec_cmd(cmd);
		free(cmd);
	}
	return (0);
}
