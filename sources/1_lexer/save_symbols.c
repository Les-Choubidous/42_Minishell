/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:12:22 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/15 09:47:15 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Identifie le type de redirection dans la chaîne d'entrée.
 *
 * Cette fonction vérifie si la chaîne contient un symbole de redirection
 * ('>', '>>', '<', '<<') et assigne le type correspondant à `type`. Elle
 * retourne un pointeur sur la position suivante après la redirection dans la
 * chaîne.
 *
 * @param str Chaîne à analyser.
 * @param type Pointeur où stocker le type de redirection détecté.
 * @return Pointeur sur le caractère après le symbole de redirection.
 */
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

/**
 * @brief Gère les redirections dans le lexer en analysant le type et les
 * guillemets.
 *
 * Cette fonction détermine le type de redirection
 * (par `identify_redirection_type`), ignore les espaces, et traite les
 * guillemets autour de la cible de redirection. Elle crée un nouveau token
 * pour la redirection et retourne la position après la redirection.
 *
 * @param str Chaîne à analyser.
 * @param new Pointeur vers un pointeur de token pour y stocker le nouveau
 *            token.
 * @return Pointeur après la redirection dans la chaîne.
 */
char	*redirection_helper(char *str, t_token **new)
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
	while (*end && !ft_isspace(*end) && !ft_strchr(SUPPORTED_SYMBOLS, *end)
		&& !((quote == SPL_QUOTES && *end == '\'') || (quote == DBL_QUOTES
				&& *end == '\"')))
		end++;
	*new = new_token(start, end, type, quote);
	if (quote != NO_QUOTES)
		end++;
	return (end);
}

/**
 * @brief Gère les symboles dans la chaîne et crée un token correspondant.
 *
 * Vérifie que les symboles sont valides, puis appelle `redirection_helper`
 * pour traiter les redirections ou crée un token pour un pipe (`|`).
 * Retourne un pointeur sur le caractère suivant le symbole.
 *
 * @param data Structure principale contenant la liste de tokens.
 * @param str Chaîne à analyser.
 * @return Pointeur après le symbole dans la chaîne.
 */
char	*save_symbol(t_data *data, char *str, int *is_new_command)
{
	t_token	*new;
	char	*ptr;
	printf("str dans save symbol : %s\n", str);
	if (check_symbol_at_end_of_string(str) || check_double_tokens(str))
		return (NULL);
	if (*str == '<' || *str == '>')
		ptr = redirection_helper(str, &new);
	else if (*str == '|')
	{
		ptr = str + 1;
		new = new_token(NULL, NULL, PIPE, NO_QUOTES);
		//*is_new_command = 1;
	}
	else
	{
		printf("Syntax error: unknown symbol %c\n", *str);
		return (NULL);
	}
	if (!new)
		return (NULL);
	lst_token_add_back(data, new);
	return (ptr);
}
