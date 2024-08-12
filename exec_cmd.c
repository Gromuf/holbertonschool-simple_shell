#include "main.h"

/**
 * exec_cmd - Exécute une commande donnée.
 *
 * @cmd: La commande à exécuter.
 *
 * Cette fonction crée un nouveau processus pour exécuter la commande
 * fournie. Si le fork échoue, un message d'erreur est affiché. Si le
 * processus enfant échoue à exécuter la commande, un message d'erreur
 * est également affiché.
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
			perror("Error");
		}
		exit(EXIT_FAILURE);
	}

	else
		wait(NULL);
}
