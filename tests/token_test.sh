#!/bin/bash

echo "Lancement de minishell en mode interactif. Saisissez vos commandes pour tester les tokens."
echo "Tapez 'exit' pour quitter."

 #Lancer minishell en mode interactif
../minishell

# Liste des commandes à tester
commands=(
    "cat|wc"
    "cat"
    "cat | ws"
    "cat file|   wc"
)

# Vérifie si Minishell est accessible
MINISHELL_PATH="../minishell"
if [ ! -x "$MINISHELL_PATH" ]; then
    echo "Erreur : Minishell introuvable ou non exécutable à l'emplacement $MINISHELL_PATH" >&2
    exit 1
fi

# Fonction pour exécuter les tests
run_tests() {
    # Affiche une bannière de démarrage
	echo "\n"
    echo "====================================="
    echo "   Démarrage des tests de Minishell  "
    echo "====================================="

    # Lance Minishell et injecte les commandes
    {
        # Pour chaque commande dans la liste
        for cmd in "${commands[@]}"; do
            # Affiche la commande en cours de test
            echo "-------------------------------------" >&2
            echo "Testing command: $cmd" >&2
            echo "-------------------------------------" >&2
            # Envoie la commande à Minishell
            echo "$cmd"
            # Pause pour une meilleure lisibilité (optionnel)
            sleep 0.2
        done

        # Ferme Minishell proprement
        echo "exit"
    } | "$MINISHELL_PATH"

    # Capture le code de sortie de Minishell
    exit_code=$?
    if [ $exit_code -ne 0 ]; then
        echo "Minishell s'est terminé avec le code $exit_code" >&2
    else
        echo "Tests terminés avec succès."
    fi
}

# Exécute les tests
run_tests
