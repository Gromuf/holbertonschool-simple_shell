#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

extern int should_exit;

void signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		/*Libérer les ressources, effectuer le nettoyage*/
		printf("\nTerminating due to SIGINT\n");
		exit(EXIT_SUCCESS);
	}
}
