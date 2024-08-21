#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* Fonction personnalisée pour formater une chaîne de caractères*/
int my_snprintf(char *buf, size_t size, const char *fmt, ...)
{
	va_list args;
	int written;

	/*Initialiser la liste des arguments*/
	va_start(args, fmt);

	/*Formater la chaîne avec vsnprintf pour éviter le débordement*/
	written = vsnprintf(buf, size, fmt, args);

	/*terminer la liste des arguments*/
	va_end(args);

	/*Assurer que la chaîne est bien terminée*/
	if (size > 0)
	{
		buf[size - 1] = '\0';
	}

	return written;
}
