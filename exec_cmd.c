#include "main.h"
#include <stdlib.h>
/*#include <stdbool.h>  Inclure pour le type bool*/

extern int should_exit; /* Variable globale pour control la sortie du shell*/
/*int should_exit = 0; Variable globale pour contrôler la sortie du shell */

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
	char *argv[256];
	char *token;
	/*int i = 0;*/
	/*int argc = 0;*/
	int argc = 0;
	int status; /* ajout pour waitpid exit*/
	/*char *executable_path = NULL;*/
	char *path_copy;
	char *cmd_copy;
	/*char *cmd_path = find_command_path(cmd);*/

	/* Make a copy of the command string*/
	cmd_copy = strdup(cmd); /* Allocate memory and copy cmd into cmd_copy*/
	if (cmd_copy == NULL)
	{
		free(cmd_copy);
		/*free(path_copy);*/
		/*perror("strdup --> cmd_copy == NULL");*/
		return;
	}

	if (is_empty_cmd(cmd_copy))
	{
		free(cmd_copy);
		/*free(path_copy);*/
		/*perror("cmd_copy-->is_empty_cmd(cmd_copy)");*/
		return;
	}

	/* Initialize argc */
	/*argc = 0;*/

	/*Tokenize the command*/
	token = strtok(cmd_copy, " \n");
	/*while (token!= NULL && argc < 255)*/
	while (token != NULL)
	{
		if (argc <= 256)
			argv[argc++] = token;
		token = strtok(NULL, " \n");
		/*argv[i++] = token;*/
		/*token = strtok(NULL, " \n");*/
	}
	/*argv[i] = NULL;*/
	argv[argc] = NULL;

	if (argv[0] != NULL)
	{
		/* Vérifiez si la commande est une commande intégrée*/
		if (strcmp(argv[0], "exit") == 0)
		{
			int exit_status = (argv[1] != NULL) ? atoi(argv[1]) : 0;
			free(cmd_copy);
			exit(exit_status);
		}
		else if (strcmp(argv[0], "env") == 0)
		{
			extern char **environ;
			char **env;
			for (env = environ; *env != NULL; ++env)
			{
				printf("%s\n", *env);
			}
			free(cmd_copy);
			return; /* Sortir de la fonction après avoir affiché les variables d'environnement*/
		}

		/* Vérifiez si le chemin est absolu*/
		if (argv[0][0] == '/')
		{
			/* Commande avec chemin absolu*/
			/*executable_path = strdup(argv[0]);*/
			path_copy = strdup(argv[0]);
		}
		else
		{
			/* Trouver le chemin complet de la commande */
			/*executable_path = which(argv[0]);*/
			/*if (executable_path == NULL)*/
			/*path_copy = which(argv[0]);*/
			path_copy = which(cmd_copy);
			/*path_copy = find_command_path(argv[0]);*/
			if (path_copy == NULL)
			{
				/*fprintf(stderr, "Command not found: %s\n", argv[0]);*/
				free(cmd_copy);
				return;
			}

		}
		pid = fork();
		if (pid == -1)

		{
			/*perror("fork PID == -1");*/
			/*perror("Fork failed");*/
			/*free(executable_path);*/
			free (path_copy);
			free(cmd_copy);
			free (cmd);
			return;
		}

		if (pid == 0)
		{
			/*Child process*/
			/*if (execve(argv[0], argv, NULL) == -1)*/
			/*if (execve(executable_path, argv, NULL) == -1)*/
			if (execve(path_copy, argv, NULL) == -1)
			{
				/*perror("Error");*/
				/*perror(argv[0]); Afficher l'erreur spécifique à la commande*/
				/*perror(argv[0]);*/
				/*perror("execve PID == 0");*/
				/*free(executable_path);*/
				/*free (path_copy);*/
				free(cmd_copy);
				exit(EXIT_FAILURE);
				/*_exit(2);  Code d'erreur pour commandes échouées */
			}
			/*free(executable_path);*/
		}
		else
		/*wait(NULL);*/
		{
			/*Parent process*/
			waitpid(pid, &status, 0); /* Attendre que le processus fils se termine*/
			if (WIFEXITED(status))
			{
				int exit_status = WEXITSTATUS(status);
				if (exit_status != 0)
				{
					/* Code d'erreur spécifique pour commandes échouées */
					/*fprintf(stderr, "Command failed with exit status %d\n", exit_status);*/
					/*perror("if execve PID == 1");*/
				}
			}
			else
			{
				/* Si le processus ne se termine pas normalement */
				/*fprintf(stderr, "Command terminated abnormally\n");*/
				/*perror("else execve PID == 1");*/
			}

			/*free(executable_path);*/
			free(path_copy);
			/*free (cmd);*/
		}
	}

	free(cmd_copy);

	return;
}
