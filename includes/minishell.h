<<<<<<< HEAD
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

//colors
# define CYAN "\e[1;96m"
# define MAGENTA "\e[1;95m"
# define RESET "\e[0m"

//listes des token
	//	> : redirection de sortie (ex : echo "Hello" > message) OUTPUT
	//	< : redirection d'entree (ex : cat < message) INPUT
	//	>> : redirection de sortie en fin de fichier APPEND
	//	<< : Heredoc
	//	| : redirection des entrees et sorties
		//int
	//cmd
		//string


#endif
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:43:29 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/11 15:01:04 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# include "../libft/libft.h"
# include "messages.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

/*****************************DATA_STRUCTURE**********************************/



/*******************************FUNCTIONS*************************************/
/********************************0_utils**************************************/

/********************************1_lexer**************************************/

/********************************2_parser*************************************/

/*******************************3_executer************************************/

/*******************************4_builtins************************************/

/*********************************5_free**************************************/


#endif
>>>>>>> 57e62ce7d6db3bfd2edd2a555df92b3f004b12ba
