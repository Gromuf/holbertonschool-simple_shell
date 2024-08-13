#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * my_exit - Terminate the program with the given exit status.
 * @status: The exit status to return to the operating system.
 *
 * This function prints a message to indicate that the program is
 * exiting and then terminates the program with the specified status code.
 */
void my_exit(int status)
{
	/* Afficher un message avant de quitter (facultatif)*/
	if (status == EXIT_SUCCESS)
	{
		printf("Exiting with success.\n");
	}
	else
	{
		printf("Exiting with error status %d.\n", status);
	}

	/* Terminer le programme avec le statut spécifié */
	exit(status);
}
