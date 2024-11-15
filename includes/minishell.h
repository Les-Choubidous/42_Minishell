/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:43:29 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/15 17:47:25 by uzanchi          ###   ########.fr       */
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
	NQ,
	SQ,
	DQ,
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
	FLAG, 		//-
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
	char		**path;
	char		*full_path;
	char		*line;

	t_env		*env;
	t_commands	*command;
	t_token		*token;
	t_in_out	input;
	t_in_out	output;
}				t_data;

/*******************************FUNCTIONS*************************************/
/*************************       0_utils       *******************************/
/*init.c*/
char			*init_full_path(char **env);
void			init_io(t_data *data);
void			add_env_lst(t_env **list, char *key, char *value);

t_env			*ft_get_env(char **env);
int				init_data(t_data *data, char **env);

/*signals.c*/
void			reset_line(int signum);
void			display_new_line(int signum);
void			signal_interactive(void);
void			signal_non_interacitve(void);

/*utils.c*/
int				ft_printf_exit_code(char *str, int exit_code);
void			print_env(t_env *list);

/*************************       1_lexer       *******************************/
/*save_symbols.c*/
char			*identify_redirection_type(char *str, t_type *type);
char			*redirection_helper(char *str, t_token **new);
char			*save_symbol(t_data *data, char *str);

/*save_wd_qt.c*/
char			*save_word(t_data *data, char *str);
char			*save_quote(t_data *data, char *str, char quote_symbol);

/*lexer_utils.c*/
int				check_symbol_at_end_of_string(char *str);
int				check_double_tokens(char *str);
t_token			*new_token(char *start, char *end, t_type type, t_quote quote);
void			lst_token_add_back(t_data *data, t_token *new);

/*lexer.c*/
static int		is_just_spaces(char *str);
int				check_user_arg(char *arg);
int				lexer(t_data *data);

/*utils_tests.c*/
void			print_tokens(t_token *token);
void			free_token(t_token *token);
void			free_token_list(t_token *head);

/*************************       2_parser      *******************************/
/******* Expander *******/
/*expander_utils.c*/
size_t			get_var_name_len(char *str);

/******** Parser ********/

/*************************      3_executer     *******************************/

/*************************      4_builtins     *******************************/

/*************************        5_free       *******************************/
/*free_lists.c*/
void			free_env_list(t_env *list);

#endif
