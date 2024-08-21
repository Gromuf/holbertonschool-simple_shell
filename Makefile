# Nom du compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Werror -Wextra -pedantic -std=gnu89

# Nom de l'exécutable
EXECUTABLE = hsh

# Fichiers sources (tous les fichiers .c dans le répertoire courant)
SOURCES = $(wildcard *.c)

# Cible par défaut
all: $(EXECUTABLE)

# Règle pour créer l'exécutable
$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(EXECUTABLE)

# Règle pour tout nettoyer et reconstruire le projet
fclean: clean

# Règle pour tout nettoyer et reconstruire le projet
re: fclean all

# Pour ne pas interférer avec des fichiers présents dans les répertoires
.PHONY: all clean fclean re
