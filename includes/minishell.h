/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:43:29 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/13 19:01:52 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "messages.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>

/*******************************MACROS***************************************/
# define SUPPORTED_SYMBOLS "<|>"

/*****************************DATA_STRUCTURE**********************************/
typedef enum e_quote
{
	NO_QUOTES,
	SPL_QUOTES,
	DBL_QUOTES,
}				t_quote;

typedef enum e_type
{
	NOTHING,
	CMD,
	ARG,		// les arguments de la string (texte)
	OUTPUT,		// >
	INPUT,		// <
	APPEND,		// >>
	HEREDOC,	// <<
	LIM,
	PIPE,
}			t_type;

typedef struct s_list
{
	char			*value;
	t_quote			quote;
	struct s_list	*next;
}					t_list;

typedef struct s_commands
{
	char				*command;
	char				**out;

	t_list				*flag;
	t_list				*arg;

	struct s_commands	*next;
}					t_commands;

typedef struct s_token
{
	char				*value;

	t_type				type;
	t_quote				quote;

	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_in_out
{
	int			fd;
	char		*value;
	t_type		type;
	t_quote		quotes;
}				t_in_out;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

/* *line correspond a *argv 
	rajout potenitel de t_env	*env
	 a la place de char **env */

typedef struct s_data
{
	char		**env;
	char		*path;
	char		*line;

	t_commands	*command;
	t_token		*token;
	t_in_out	input;
	t_in_out	output;
}				t_data;

/*******************************FUNCTIONS*************************************/
/*************************       0_utils       *******************************/
/*signals.c*/
void	reset_line(int signum);
void	display_new_line(int signum);
void	signal_interactive(void);
void	signal_non_interacitve(void);

/*************************       1_lexer       *******************************/

/*************************       2_parser      *******************************/

/*************************      3_executer     *******************************/

/*************************      4_builtins     *******************************/

/*************************        5_free       *******************************/

#endif
