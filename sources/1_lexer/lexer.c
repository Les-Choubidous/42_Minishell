/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:12:51 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/13 00:39:10 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
}
