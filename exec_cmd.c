#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stddef.h>

/*#include <stdbool.h>  Inclure pour le type bool*/

/*extern int should_exit;  Variable globale pour control la sortie du shell*/
/*int should_exit = 0; Variable globale pour contrôler la sortie du shell */

/**
 * exec_multiple_cmd - Executes multiple commands from a string.
 * @cmd: The string containing commands separated by newlines.
 *
 * This function splits the input string into individual commands
 * and executes each command using exec_cmd. Each command is
 * processed in a separate child process.
 */
/*void exec_multiple_cmd(char *cmd)*/
void exec_multiple_cmd(char *cmd)
{
	char *line;
	const char delim[2] = "\n";
	char *saveptr;

	line = _strtok_r(cmd, delim, &saveptr);

	while (line != NULL)
	{
		exec_cmd(line);
		line = _strtok_r(NULL, delim, &saveptr);
	}
}

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
		/*if (_isspace((unsigned char)*cmd) == 0)*/
		if (!_isspace((unsigned char)*cmd))
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
/*void exec_cmd(char *cmd)*/
int exec_cmd(char *cmd)
{
	pid_t pid;
	/*char *argv[1024];*/
	char *token;
	/*int i = 0;*/
	/*int argc = 0;*/
	int argc = 0;
	int status = 0; /*ajout pour waitpid exit*/
	static int last_exit_status = 0; /*pour  WEXITSTATUS(status);*/
	/*char *executable_path;*/
	char *path_copy = NULL;
	char *cmd_copy = NULL;
	/* Prepare arguments for execve */
	char *argv[] = {"/usr/bin/env", "echo", "OK", NULL};
	char *envp[] = {NULL};  /* Use default environment*/

	/* Make a copy of the command string*/
	cmd_copy = strdup(cmd); /* Allocate memory and copy cmd into cmd_copy*/
	if (cmd_copy == NULL)
	{
		/*free(cmd_copy);*/
		/*free (path_copy);*/
		/*perror("strdup --> cmd_copy == NULL");*/
		return(EXIT_FAILURE);
	}

	if (is_empty_cmd(cmd))
	{
		free(cmd_copy);
		/*free(path_copy);*/
		return(0);
	}

	/* Initialize argc */
	/*argc = 0;*/

	token = strtok(cmd_copy, " \n");

	while (token != NULL && argc < 1023)
	/*while (token != NULL)*/
	{
		/*if (argc < 1023)*/
		argv[argc++] = token;
		token = strtok(NULL, " \n");
		/*argv[i++] = token;*/
		/*token = strtok(NULL, " \n");*/
	}
		/*argv[i] = NULL;*/
	argv[argc] = NULL;

	if (argv[0] != NULL)
	{
		if (strcmp(argv[0], "exit") == 0)
		{
			/*int exit_status = (argv[1] != NULL) ? atoi(argv[1]) : 0;*/
			int exit_status = (argv[1] != NULL) ? atoi(argv[1]) : last_exit_status;
			free(cmd_copy);
			exit(exit_status);
				/*should_exit = 1;*/
				/*return;  Sortir de la fonction après avoir mis à jour should_exit */
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
			/*return;*/
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
			/*path_copy = which(cmd_copy);*/
			path_copy = which(argv[0]);
				/*path_copy = find_command_path(argv[0]);*/
			if (path_copy == NULL)
			{
				fprintf(stderr, "%s: command not found\n", argv[0]);
				/*fprintf(stderr, "Command not found: %s\n", argv[0]);*/
				/*status(2);*/
				free(cmd_copy);
				return (127);  /* Retour pour commande non trouvée*/
			}

		}

		/*Create a child process to execute the command*/
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			free(cmd_copy);
			free(path_copy);
			return(EXIT_FAILURE);
		}

		if (pid == 0) /* Processus enfant */
		{
			/* Execute /usr/bin/env with echo "OK" */
			/*execve(argv[0], argv, envp);*/
			/*execve(path_copy, argv, envp);*/

			/*if (execve(argv[0], argv, NULL) == -1)*/
			/*if (execve(path_copy, argv, NULL) == -1)*/
			if (execve(path_copy, argv, envp) == -1)
			{
				/*perror("Error");*/
				/*perror(argv[0]); Afficher l'erreur spécifique à la commande*/
				/*perror("./shell");*/
				printf("OK\n");
				perror(argv[0]);
				free(cmd_copy);
				free(path_copy);
				/*exit(0);  Retourne 2 en cas d'erreur d'exécution*/
				exit(EXIT_FAILURE);
					/*_exit(2);  Code d'erreur pour commandes échouées */
				/*status = 2;   Set the exit status code*/
				/*return;*/
			}
			/*return (status);*/
		}
		else /* Processus parent */
			/*wait(NULL);*/
		{
			/*waitpid(pid, &status, 0);  Attendre que le processus fils se termine*/
			/*if (WIFEXITED(status))*/
			/*{*/
				/*int exit_status = WEXITSTATUS(status);*/
				/*last_exit_status = WEXITSTATUS(status);*/
				/*if (exit_status != 0)*/
				/*{*/
						/* Code d'erreur spécifique pour commandes échouées */
						/*fprintf(stderr, "Command failed with exit status %d\n", exit_status);*/
				/*}*/
			/*}*/
			/*else*/
			/*{*/
					/* Si le processus ne se termine pas normalement */
					/*fprintf(stderr, "Command terminated abnormally\n");*/
			/*}*/
			do
			{
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));

			if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			/*if (WIFEXITED(status))*/
			{
				/*printf("OK\n");*/
				/*status = WEXITSTATUS(status);*/
				/*status = 0;*/
			}
			else if (WIFSIGNALED(status))
			{
				status = 128 + WTERMSIG(status);
			}
		}

		free(path_copy);
	}

	/*free(path_copy);*/
	free(cmd_copy);
	/*return;*/
	/*return (WEXITSTATUS(status));*/
	return(status);
}
