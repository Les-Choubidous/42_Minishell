/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:29:55 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/12 15:59:11 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*Ctrl C affiche nouvel ligne 
Ctrl + D exit the shell*/

void    reset_line(int signum)
{
    (void)signum;
    rl_replace_line("", 0);
    rl_on_new_line();
    write(1, "\n", STDERR_FILENO);
    rl_redisplay();
}

void    display_new_line(int sig)
{
    if (sig == SIGQUIT)
        printf("Quit (core dumped)\n");
    write(1, "\n", STDERR_FILENO);
    rl_on_new_line();
}

void    signal_ON(void)
{
    signal(SIGINT, reset_line);
    signal(SIGQUIT, SIG_IGN);
}

void    signal_OFF(void)
{
    signal(SIGINT, display_new_line);
    signal(SIGQUIT, display_new_line);
}
