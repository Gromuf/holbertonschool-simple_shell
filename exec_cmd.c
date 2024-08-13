#include "main.h"
/*#include <stdbool.h>  Inclure pour le type bool*/

/*extern int should_exit;  Variable globale pour control la sortie du shell*/
int should_exit = 0; /* Variable globale pour contrôler la sortie du shell */

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
	/*int i = 0;*/
	/*int argc = 0;*/
	int argc;
	int status; /* ajout pour waitpid exit*/
	char *executable_path;

	if (is_empty_cmd(cmd))
		return;

	/* Initialize argc */
	argc = 0;

	token = strtok(cmd, " \n");
	while (token != NULL)
	{
		argv[argc++] = token;
		token = strtok(NULL, " ");
		/*argv[i++] = token;*/
		/*token = strtok(NULL, " \n");*/
	}
	/*argv[i] = NULL;*/
	argv[argc] = NULL;

	if (argv[0] != NULL)
	{
		if (strcmp(argv[0], "exit") == 0)
		{
			should_exit = 1;
			return; /* Sortir de la fonction après avoir mis à jour should_exit */
					/*Si la commande est "exit", sortir du shell*/
					/*if (strcmp(argv[0], "exit") == 0)*/
					/* Si un argument est fourni, utiliser ce code de sortie */
					/*if (argv[1] != NULL)*/
					/*{*/
					/*should_exit = 1;*/
					/*return;  Sortir de la fonction après avoir mis à jour should_exit */
					/*int exit_code = atoi(argv[1]);*/
					/*exit(exit_code);*/
					/*should_exit = exit_code;*/
					/*should_exit = atoi(argv[1]);  Mettre à jour should_exit */
					/*}*/
					/*else*/
					/*{*/
					/*should_exit = 0;*/
					/* Sinon, utiliser le code de sortie 0 */
					/*exit(EXIT_SUCCESS);*/
					/*}*/
					/*return;*/
		}
		else if (strcmp(argv[0], "env") == 0)
		{
			/* Si la commande est "env", afficher les variables d'environnement */
			extern char **environ;
			char **env;

			for (env = environ; *env != NULL; ++env)
			{
				printf("%s\n", *env);
			}
			return; /* Sortir de la fonction après avoir affiché les variables d'environnement */
		}
	}

	/* Trouver le chemin complet de la commande */
	executable_path = find_executable(argv[0]);
	if (executable_path == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", argv[0]);
		return;
	}

	pid = fork();

	if (pid == -1)
	{
		perror("Fork failed");
		free(executable_path);
		return;
	}

	if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			/*perror("Error");*/
			/*perror(argv[0]); Afficher l'erreur spécifique à la commande*/
			perror("./shell");
			free(executable_path);
			exit(EXIT_FAILURE);
			/*_exit(2);  Code d'erreur pour commandes échouées */
		}
	}
	else
	/*wait(NULL);*/
	{
		waitpid(pid, &status, 0); /* Attendre que le processus fils se termine*/
		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);
			if (exit_status != 0)
			{
				/* Code d'erreur spécifique pour commandes échouées */
				/*fprintf(stderr, "Command failed with exit status %d\n", exit_status);*/
			}
		}
		else
		{
			/* Si le processus ne se termine pas normalement */
			/*fprintf(stderr, "Command terminated abnormally\n");*/
		}
		free(executable_path);
	}
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
