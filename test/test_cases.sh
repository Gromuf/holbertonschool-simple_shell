#!/bin/bash

# Définir la commande pour exécuter le shell
SHELL_CMD="./hsh"

# Fonction pour exécuter une commande et vérifier le résultat
run_test() {
    local description="$1"
    local command="$2"
    local expected="$3"

    echo "$description"
    output=$($SHELL_CMD -c "$command")
    if [[ "$output" == "$expected" ]]; then
        echo "Test réussi"
    else
        echo "Test échoué"
        echo "Sortie obtenue:"
        echo "$output"
        echo "Sortie attendue:"
        echo "$expected"
    fi
}

# Test des différents cas

# Test 1: Exécution de `ls`
run_test "Test 1: Exécution de ls" "ls" "$(ls)"

# Test 2: Copier /bin/ls en hbtn_ls dans le répertoire parent et exécuter ./.././../hbtn_ls /var
cp /bin/ls hbtn_ls
run_test "Test 2: Exécution de .././../hbtn_ls /var" "./.././../hbtn_ls /var" "$(ls /var)"

# Test 3: Exécuter `ls -l`
run_test "Test 3: Exécution de ls -l" "ls -l" "$(ls -l)"

# Test 4: Exécuter /bin/ls /var
run_test "Test 4: Exécution de /bin/ls /var" "/bin/ls /var" "$(ls /var)"

# Test 5: Copier /bin/ls en hbtn_ls dans le répertoire parent et exécuter ../hbtn_ls /var
cp /bin/ls ../hbtn_ls
run_test "Test 5: Exécution de ../hbtn_ls /var" "../hbtn_ls /var" "$(ls /var)"

# Test 6: Copier /bin/ls en hbtn_ls dans le répertoire parent et exécuter ../../hbtn_ls /var
cp /bin/ls ../../hbtn_ls
run_test "Test 6: Exécution de ../../hbtn_ls /var" "../../hbtn_ls /var" "$(ls /var)"

# Test 7: Copier /bin/ls en hbtn_ls dans le répertoire parent et exécuter ./.././../////././hbtn_ls /var
cp /bin/ls ./.././../hbtn_ls
run_test "Test 7: Exécution de ./.././../////././hbtn_ls /var" "./.././../hbtn_ls /var" "$(ls /var)"

# Test 8: Exécuter `/bin/ls`
run_test "Test 8: Exécution de /bin/ls" "/bin/ls" "$(ls)"

# Test 9: `/bin` est le dernier élément de PATH, exécuter `ls`
export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
run_test "Test 9: Exécution de ls avec /bin comme dernier élément de PATH" "ls" "$(ls)"

# Test 10: Exécuter /bin/ls (entouré d'espaces) (grand)
run_test "Test 10: Exécution de /bin/ls (entouré d'espaces) (grand)" "   /bin/ls   " "$(ls)"

# Test 11: Supprimer la variable d'environnement PATH et exécuter /bin/ls
export PATH=""
run_test "Test 11: Exécution de /bin/ls sans PATH" "/bin/ls" "$(ls)"

# Test 12: Exécuter /bin/ls -l
run_test "Test 12: Exécution de /bin/ls -l" "/bin/ls -l" "$(ls -l)"

# Test 13: Exécuter à la fois /bin/ls et ls plusieurs fois avec des lignes vides et des espaces de début et de fin
run_test "Test 13: Exécution de /bin/ls et ls plusieurs fois avec des espaces" "ls\n/bin/ls\n\n   ls   \n/bin/ls" "$(ls)\n$(ls)"

# Test 14: Exécuter `ls` 4 fois (avec espaces de début et de fin)
run_test "Test 14: Exécution de ls 4 fois (avec espaces)" "   ls   \n   ls   \n   ls   \n   ls   " "$(ls)\n$(ls)\n$(ls)\n$(ls)"

# Test 15: Définir PATH comme une chaîne vide et exécuter `ls`
export PATH=""
run_test "Test 15: Exécution de ls avec PATH vide" "ls" "$(ls)"

# Test 16: Exécuter /bin/ls 4 fois (entouré d'espaces)
run_test "Test 16: Exécution de /bin/ls 4 fois (entouré d'espaces)" "   /bin/ls   \n   /bin/ls   \n   /bin/ls   \n   /bin/ls   " "$(ls)\n$(ls)\n$(ls)\n$(ls)"

# Test 17: Copier /bin/ls en hbtn_ls (dans le répertoire courant) et exécuter ./hbtn_ls /var
cp /bin/ls ./hbtn_ls
run_test "Test 17: Exécution de ./hbtn_ls /var" "./hbtn_ls /var" "$(ls /var)"

# Test 18: Copier le fichier /bin/ls en .hbtnls (dans le répertoire courant), changer PATH pour pointer vers PWD et exécuter .hbtnls /var
cp /bin/ls .hbtnls
export PATH="$(pwd)"
run_test "Test 18: Exécution de .hbtnls /var avec PATH comme PWD" ".hbtnls /var" "$(ls /var)"

# Test 19: Supprimer toutes les variables d'environnement et exécuter `ls`
unset $(env | awk -F= '{print $1}')
run_test "Test 19: Exécution de ls après suppression de toutes les variables d'environnement" "ls" "$(ls)"

# Test 20: `/bin` est le premier élément de PATH, exécuter `ls`
export PATH="/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin"
run_test "Test 20: Exécution de ls avec /bin comme premier élément de PATH" "ls" "$(ls)"

# Test 21: Supprimer toutes les variables d'environnement et définir une variable PATH1, puis exécuter `ls`
unset $(env | awk -F= '{print $1}')
export PATH1="/bin"
run_test "Test 21: Exécution de ls avec PATH1 seulement" "ls" "$(ls)"

# Test 22: Copier le fichier /bin/ls en hbtn_ls (dans le répertoire courant), définir le PATH sur PWD et exécuter hbtn_ls /var
cp /bin/ls ./hbtn_ls
export PATH="$(pwd)"
run_test "Test 22: Exécution de hbtn_ls /var avec PATH comme PWD" "hbtn_ls /var" "$(ls /var)"

# Test 23: fork ne doit pas être appelé lorsqu'une commande n'existe pas
run_test "Test 23: fork ne doit pas être appelé lorsqu'une commande n'existe pas" "non_existent_command" "command not found"

# Nettoyer les fichiers copiés
rm -f ../hbtn_ls ./hbtn_ls .hbtnls

echo "Tous les tests sont terminés."
