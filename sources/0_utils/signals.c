/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:29:55 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/12 18:30:07 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Gère le signal SIGINT (Ctrl + C) en mode interactif.
 * 
 * Efface la ligne en cours dans le buffer de `readline`, déplace le curseur
 * vers une nouvelle ligne, et réaffiche le prompt. Cela permet de ne pas
 * quitter le shell lorsque l'utilisateur appuie sur Ctrl + C, mais seulement
 * d'interrompre la saisie en cours et de revenir au prompt.
 * 
 * @param signum Numéro du signal (non utilisé, il est donc casté en void).
 */
void    reset_line(int signum)
{
    (void)signum;                       // Pour éviter un warning de compilation    
    rl_replace_line("", 0);             // Efface la ligne en cours
    rl_on_new_line();                   // Indique que le curseur est sur une nouvelle ligne
    write(1, "\n", STDERR_FILENO);      // Affiche une nouvelle ligne sur la sortie standard
    rl_redisplay();                     // Réaffiche le prompt après l'effacement de la ligne
}

/**
 * @brief Gère le signal SIGQUIT (Ctrl + \) ou SIGINT en affichant un retour
 * à la ligne.
 * 
 * Affiche une nouvelle ligne lorsqu'un signal d'interruption (SIGINT) ou
 * d'abandon (SIGQUIT) est reçu. Si le signal est SIGQUIT, affiche également
 * un message indiquant la terminaison "core dumped".
 * 
 * @param signum Numéro du signal reçu.
 */
void    display_new_line(int signum)
{
    if (signum == SIGQUIT)
        printf("Quit (core dumped)\n"); // Affiche un message pour SIGQUIT
    write(1, "\n", STDERR_FILENO);      // Affiche une nouvelle ligne sur la sortie standard
    rl_on_new_line();                   // Indique que le curseur est sur une nouvelle ligne
}

/**
 * @brief Active la gestion des signaux en mode interactif.
 * 
 * Associe le signal SIGINT (Ctrl + C) à la fonction `reset_line`,
 * qui efface la ligne en cours. Ignore le signal SIGQUIT (Ctrl + \)
 * pour éviter de terminer le shell en mode interactif.
 */
void    signal_interactive(void)
{
    signal(SIGINT, reset_line);     // Associe SIGINT à `reset_line` pour effacer la ligne
    signal(SIGQUIT, SIG_IGN);       // Ignore SIGQUIT pour éviter de quitter le shell
}

/**
 * @brief Active la gestion des signaux en mode non interactif.
 * 
 * Associe les signaux SIGINT (Ctrl + C) et SIGQUIT (Ctrl + \) à la fonction
 * `display_new_line`, qui affiche une nouvelle ligne et un message pour
 * SIGQUIT (si reçu), sans quitter immédiatement le shell.
 */
void    signal_non_interacitve(void)
{
    signal(SIGINT, display_new_line);   // Associe SIGINT à `display_new_line`
    signal(SIGQUIT, display_new_line);  // Associe SIGQUIT à `display_new_line`
}
