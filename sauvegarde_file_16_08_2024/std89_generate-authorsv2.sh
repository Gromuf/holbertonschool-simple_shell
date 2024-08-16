#!/bin/sh

# Arrête le script en cas d'erreur
set -e

# Définit le répertoire racine du dépôt
ROOTDIR=$(git rev-parse --show-toplevel)

# Active le mode débogage (optionnel)
set -x

# Génére le fichier AUTHORS
{
	echo "# This file lists all individuals who have contributed content to the repository."
	echo "# It is generated automatically from the Git commit history."
	echo ""

	# Liste les auteurs uniques
	git -C "$ROOTDIR" log --format='%aN <%aE>' | LC_ALL=C sort -uf
} > "$ROOTDIR/AUTHORS"
