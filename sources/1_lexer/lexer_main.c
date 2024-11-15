/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:12:51 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/15 16:01:13 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/messages.h"

/**
 * @brief Vérifie si une chaîne ne contient que des espaces.
 * 
 * Parcourt `arg` et retourne `1` si la chaîne est constituée uniquement
 * d'espaces, sinon `0`.
 * 
 * @param arg Chaîne à analyser.
 * @return `1` si la chaîne contient uniquement des espaces, `0` sinon.
 */
static int	is_just_spaces(char *arg)
{
	while (*arg)
	{
		if (!ft_isspace(*arg++))
			return (0);
	}
	return (1);
}

/**
 * @brief Vérifie la validité des arguments utilisateur.
 * 
 * Vérifie si `arg` est vide ou ne contient que des espaces, ou si elle
 * commence par un pipe, et gère les erreurs de syntaxe pour les quotes
 * non fermées.
 * 
 * @param arg Chaîne d'arguments.
 * @return `EXIT_FAILURE` en cas d'erreur, `EXIT_SUCCESS` sinon.
 */
int	check_user_arg(char *arg)
{
	if (!arg)
		return (EXIT_FAILURE);
	if (is_just_spaces(arg))
		return (EXIT_FAILURE);
	while (ft_isspace(*arg))
		arg++;
	if (*arg == '|')
		return (ft_printf_exit_code(UNEXPECTED_PIPE, EXIT_FAILURE));
	while (*arg)
	{
		if (*arg == '\'' || *arg == '\"')
		{
			arg = ft_strchr(arg + 1, *arg);
			if (arg == NULL)
				return (ft_printf_exit_code(UNCLOSED_QUOTE, EXIT_FAILURE));
				/*return(printf("Syntax error: unclosed quote in argument\n"), 1); les deux se correspondent */
			else
				arg++;
		}
		else
			arg++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Fonction principale du lexer.
 * 
 * Parcourt `data->line` pour analyser chaque caractère et identifier les mots,
 * redirections, pipes, ou citations, en créant des tokens correspondants et en
 * les ajoutant à la liste des tokens.
 * 
 * @param data Structure principale contenant la ligne de commande et la liste
 * des tokens.
 * @return `EXIT_FAILURE` en cas d'erreur, `EXIT_SUCCESS` sinon.
 */
int	lexer(t_data *data)
{
	char *str;

	str = data->line;
	if (check_user_arg(str))
		return (EXIT_FAILURE);
	while (*str)
	{
		if (ft_isspace(*str))
			str++;
		else if (ft_strchr(SUPPORTED_SYMBOLS, *str))
			str = save_symbol(data, str);
		else if (*str == '\'' || *str == '\"')
			str = save_quote(data, str + 1, *str);
		else
			str = save_word(data, str);
		if (!str)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
