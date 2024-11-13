/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:43:29 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/13 15:52:12 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Created: 2024/11/11 14:43:29 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/11 17:19:31 by memotyle         ###   ########.fr       */
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

/*****************************DATA_STRUCTURE**********************************/
typedef enum e_quote
{
	NO_QUOTES,	//
	S_QUOTES,	//''
	D_QUOTES,	//""

}				t_quote;

typedef enum e_type
{
	OUTPUT,		//>
	INPUT,		//<
	APPEND,		//>>
	HEREDOC,	//<<

	PIPE,		//|

	STDIN,
	STDOUT,

	CMD,

}			t_type;

typedef struct s_list
{
		char			*value;
		t_quote			quote;
		struct s_list	*next;
}						t_list;


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

typedef struct s_data
{

	char		*full_path;
	char		**path;

	t_env		*env;
	t_commands	*command;
	t_token		*token;
	t_in_out	input;
	t_in_out	output;
}				t_data;

/*******************************FUNCTIONS*************************************/
/*************************       0_utils       *******************************/
/*init.c*/
char	*init_full_path(char **env);
void	init_io(t_data *data);

t_env	*create_node(const char *env_part);
t_env	*ft_get_env(char **env);
void	free_env_list(t_env *env_list);

int		init_data(t_data *data, char **env);

/*************************       1_lexer       *******************************/

/*************************       2_parser      *******************************/

/*************************      3_executer     *******************************/

/*************************      4_builtins     *******************************/

/*************************        5_free       *******************************/

/*************************        6_tests       *******************************/
void	print_env(t_env *print);
#endif
