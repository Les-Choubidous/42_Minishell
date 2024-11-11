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
