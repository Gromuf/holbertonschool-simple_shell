#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_test(const char *description, const char *command, const char *expected_output)
{
	printf("%s\n", description);

	/* Exécuter la commande et rediriger la sortie vers un fichier temporaire*/
	system("rm -f /tmp/output.txt"); /*Nettoyer le fichier de sortie*/
	char cmd[256];
	snprintf(cmd, sizeof(cmd), "%s > /tmp/output.txt 2>&1", command);
	system(cmd);

	/*Lire le contenu du fichier de sortie*/
	FILE *file = fopen("/tmp/output.txt", "r");
	if (!file)
	{
		perror("Erreur lors de l'ouverture du fichier de sortie");
		exit(EXIT_FAILURE);
	}

	/* Lire la sortie*/
	char output[1024];
	size_t len = fread(output, 1, sizeof(output) - 1, file);
	fclose(file);
	output[len] = '\0';

	/* Comparer la sortie avec la sortie attendue*/
	if (strcmp(output, expected_output) == 0)
	{
		printf("Test réussi\n");
	}
	else
	{
		printf("Test échoué\n");
		printf("Sortie obtenue:\n%s\n", output);
		printf("Sortie attendue:\n%s\n", expected_output);
	}
}

int main()
{
	/*Cas de test*/
	run_test("Test 1: Exécution de ls", "ls", "ls"); /* Attendez-vous à ce que `ls` génère une liste de fichiers et répertoires*/
	run_test("Test 2: Copier /bin/ls en hbtn_ls dans le répertoire parent et exécuter ./.././../hbtn_ls /var",
			 "cp /bin/ls ../hbtn_ls && ./.././../hbtn_ls /var", "ls /var"); /* Vous devez ajuster cette sortie*/
	run_test("Test 3: Exécuter ls -l", "ls -l", "ls -l");					/*Attendez-vous à une sortie longue*/
	run_test("Test 4: Exécuter /bin/ls /var", "/bin/ls /var", "ls /var");	/* Liste les fichiers dans /var*/
	run_test("Test 5: Copier /bin/ls en hbtn_ls dans le répertoire parent et exécuter ../hbtn_ls /var",
			 "cp /bin/ls ../hbtn_ls && ../hbtn_ls /var", "ls /var"); /* Vous devez ajuster cette sortie*/
	run_test("Test 6: Copier /bin/ls en hbtn_ls dans le répertoire parent et exécuter ../../hbtn_ls /var",
			 "cp /bin/ls ../../hbtn_ls && ../../hbtn_ls /var", "ls /var"); /* Vous devez ajuster cette sortie*/
	run_test("Test 7: Copier /bin/ls en hbtn_ls dans le répertoire parent et exécuter ./.././../////././hbtn_ls /var",
			 "cp /bin/ls ./.././../hbtn_ls && ./.././../////././hbtn_ls /var", "ls /var");																// Vous devez ajuster cette sortie
	run_test("Test 8: Exécuter /bin/ls", "/bin/ls", "ls");																								// Attendez-vous à ce que `ls` génère une liste de fichiers et répertoires
	run_test("Test 9: /bin est le dernier élément de PATH, exécuter ls", "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin ls", "ls"); // Vous devez ajuster cette sortie
	run_test("Test 10: Exécuter /bin/ls (entouré d'espaces) (grand)", "   /bin/ls   ", "ls");															// Vous devez ajuster cette sortie
	run_test("Test 11: Supprimer la variable d'environnement PATH et exécuter /bin/ls", "unset PATH && /bin/ls", "ls");									// Vous devez ajuster cette sortie
	run_test("Test 12: Exécuter /bin/ls -l", "/bin/ls -l", "ls -l");																					// Attendez-vous à une sortie longue
	run_test("Test 13: Exécuter à la fois /bin/ls et ls plusieurs fois avec des lignes vides et des espaces de début et de fin",
			 "/bin/ls\nls\n\n   ls   \n/bin/ls", "ls\nls\n\nls\nls");																				  // Vous devez ajuster cette sortie
	run_test("Test 14: Exécuter ls 4 fois (avec espaces de début et de fin)", "   ls   \n   ls   \n   ls   \n   ls   ", "ls\nls\nls\nls");			  // Vous devez ajuster cette sortie
	run_test("Test 15: Définir PATH comme une chaîne vide et exécuter ls", "PATH= ls", "ls");														  // Vous devez ajuster cette sortie
	run_test("Test 16: Exécuter /bin/ls 4 fois (entouré d'espaces)", "   /bin/ls   \n   /bin/ls   \n   /bin/ls   \n   /bin/ls   ", "ls\nls\nls\nls"); // Vous devez ajuster cette sortie
	run_test("Test 17: Copier /bin/ls en hbtn_ls (dans le répertoire courant) et exécuter ./hbtn_ls /var",
			 "cp /bin/ls ./hbtn_ls && ./hbtn_ls /var", "ls /var"); /* Vous devez ajuster cette sortie*/
	run_test("Test 18: Copier le fichier /bin/ls en .hbtnls (dans le répertoire courant), changer PATH pour pointer vers PWD et exécuter .hbtnls /var",
			 "cp /bin/ls .hbtnls && PATH=$(pwd) ./.hbtnls /var", "ls /var");																			 // Vous devez ajuster cette sortie
	run_test("Test 19: Supprimer toutes les variables d'environnement et exécuter ls", "unset $(env | awk -F= '{print $1}') && ls", "ls");				 // Vous devez ajuster cette sortie
	run_test("Test 20: /bin est le premier élément de PATH, exécuter ls", "PATH=/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin ls", "ls"); // Vous devez ajuster cette sortie
	run_test("Test 21: Supprimer toutes les variables d'environnement et définir une variable PATH1, puis exécuter ls",
			 "unset $(env | awk -F= '{print $1}') && PATH1=/bin ls", "ls"); /* Vous devez ajuster cette sortie*/
	run_test("Test 22: Copier le fichier /bin/ls en hbtn_ls (dans le répertoire courant), définir le PATH sur PWD et exécuter hbtn_ls /var",
			 "cp /bin/ls ./hbtn_ls && PATH=$(pwd) ./hbtn_ls /var", "ls /var");														 // Vous devez ajuster cette sortie
	run_test("Test 23: fork ne doit pas être appelé lorsqu'une commande n'existe pas", "non_existent_command", "command not found"); // Vous devez ajuster cette sortie

	/* Nettoyer les fichiers copiés*/
	system("rm -f ../hbtn_ls ./hbtn_ls .hbtnls");

	printf("Tous les tests sont terminés.\n");

	return 0;
}
