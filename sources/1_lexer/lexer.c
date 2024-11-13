/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:12:51 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/13 17:03:32 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***********************     SAVE SYMBOLS     *********************************/

char	*identify_redirection_type(char *str, t_type *type)
{
	if (*str == '>')
	{
		if (*(str + 1) == '>')
		{
			*type = APPEND;
			return (str + 2);
		}
		*type = OUTPUT;
		return (str + 1);
	}
	if (*str == '<')
	{
		if (*(str + 1) == '<')
		{
			*type = HEREDOC;
			return (str + 2);
		}
		*type = INPUT;
		return (str + 1);
	}
	return (str);
}

char	*lexer_helper(char *str, t_token **new)
{
	t_type	type;
	t_quote	quote;
	char	*start;
	char	*end;

	start = identify_redirection_type(str, &type);
	while (*start && ft_isspace(*start))
		start++;
	quote = NO_QUOTES;
	if (*start == '\'' || *start == '\"')
	{
		if (*start == '\'')
			quote = SPL_QUOTES;
		else
			quote = DBL_QUOTES;
		start++;
	}
	end = start;
	while (*end && !ft_isspace(*end) && !ft_strchr(SUPPORTED_SYMBOLS, *end) && !((quote == SPL_QUOTES && *end == '\'') || (quote == DBL_QUOTES && *end == '\"')))
		end++;
	*new = new_token(start, end, type, quote);
	if (quote != NO_QUOTES)
		end++;
	return (end);
}

char	*save_symbol(t_data *data, char *str)
{
	t_token	*new;
	char	*ptr;

	if (/*truc qui check la fin de la string || un truc qui check les doubles tokens;	les deux prennent str en parametre*/)
		return (NULL);
	if (*str == '<' || *str == '>')
		ptr = lexer_helper(str, &new);
	if (*str == '|')
	{
		ptr = str + 1;
		new = new_token(NULL, NULL, PIPE, NO_QUOTES);
	}
	if (!new)
		return (NULL);
	lst_token_add_back(data, new);
	return (ptr);
}

/***********************     SAVE WD QOT     *********************************/

char	*save_word()
{
	
}

char	*save_quote()
{
	
}

/***********************     LEXER UTILS     *********************************/


t_token	*new_token(char *start, char *end, t_type type, t_quote quote)
{
	t_token *new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		perror("malloc error");
		return (NULL);
	}
	if (start)
	{
		new->value = ft_substr(start, 0, end - start); // ou bien = malloc(sizeof(char) * (end - start + 1));
		if (!new->value)
		{
			perror("token value malloc");
			free(new);
			return (NULL);
		}
	}
	else
		new->value = NULL;
	new->type = type;
	new->quote = quote;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	lst_token_add_back(t_data *data, t_token *new)
{
	t_token	*tmp;

	if (!data->token)
	{
		new->prev = NULL;
		data->token = new;
		return;
	}
	else
	{
		tmp = data->token;
		while (tmp->next)
			tmp = tmp->next;
		new->prev = tmp;
		tmp->next = new;
	}
}

/***********************     LEXER MAIN      *********************************/

static int	is_just_spaces(char *arg)
{
	while (*arg)
	{
		if (!ft_isspace(*arg++))
			return (0);
	}
	return (1);
}

int	check_user_arg(char *arg)
{
	
}

int	lexer(t_data *data)
{
	char	*str;

	str = data->line;
	if (check_user_arg(str /*ou data->line*/))
		return (EXIT_FAILURE);
	while (*str)
	{
		if (ft_isspace(*str))
			str++;
		else if (ft_strchr(SUPPORTED_SYMBOLS, *str))
		{
			str = save_symbol(data, str);
			if (!str)
				return (EXIT_FAILURE);
		}
		else if (*str == '\'' || *str == '\"')
		{
			str = save_quote(data, str);
			if (!str)
				return (EXIT_FAILURE);
		}
		else
		{
			str = save_word(data, str);
			if (!str)
				return (EXIT_FAILURE);
		}
		if (str == NULL)
			return (EXIT_FAILURE);
	}
}