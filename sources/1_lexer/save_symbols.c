/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:12:22 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/15 20:23:39 by memotyle         ###   ########.fr       */
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
	printf("print str dans identify : %s\n", str);
	if (*str == '>')
	{
		if (*(str) == '>')
		{
			*type = APPEND;
			return (str + 1);
		}
		*type = OUTPUT;
		return (str + 1);
	}
	if (*str == '<')
	{
		if (*(str + 1) == '<')
		{
			*type = HEREDOC;
			return (str + 1);
		}
		*type = INPUT;
		return (str + 1);
	}
	return (str + 1);
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
char	*redirection_helper(t_data *data, char *str, t_token **new_symbol,
		t_token **new_target)
{
	t_type	type;
	t_quote	quote;
	char	*start;
	char	*end;

	quote = NQ;
	// Identifier le type de redirection
	start = identify_redirection_type(str, &type);
	start++;                            // Passer le premier chevron
	if (*start == '>' || *start == '<') // Si c'est un double chevron (>>, <<)
		start++;
	// Créer un token pour le symbole de redirection
	*new_symbol = new_token(NULL, NULL, type, NQ);
	if (!*new_symbol)
		return (NULL);
	// Ignorer les espaces après la redirection
	while (*start && ft_isspace(*start))
		start++;
	// Gérer les guillemets autour de la cible
	if (*start == '\'' || *start == '\"')
	{
		quote = (*start == '\'') ? SQ : DQ;
		start++;
	}
	// Trouver la fin de la cible
	end = start;
	while (*end && !ft_isspace(*end) && !ft_strchr(SUPPORTED_SYMBOLS, *end))
	{
		if ((quote == SQ && *end == '\'') || (quote == DQ && *end == '\"'))
			break ;
		end++;
	}
	// Créer un token pour la cible de la redirection
	*new_target = new_token(start, end, ARG, quote);
	if (quote != NQ && *end == '\'' || *end == '\"')
		end++;
	return (end); // Retourner la position après la cible
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
	t_token	*new_symbol;
	t_token	*new_target;
	char	*ptr;

	new_symbol = NULL;
	new_target = NULL;
	// Vérifier les erreurs sur les symboles
	if (check_double_tokens(str))
		return (NULL);
	if (check_symbol_at_end_of_string(str))
		return (NULL);
	// Gestion des symboles
	if (*str == '<' || *str == '>')
	{
		// Gérer les redirections
		ptr = redirection_helper(data, str, &new_symbol, &new_target);
		// Ajouter les deux tokens à la liste
		if (new_symbol)
			lst_token_add_back(data, new_symbol);
		if (new_target)
			lst_token_add_back(data, new_target);
	}
	else if (*str == '|')
	{
		// Gérer le pipe
		ptr = str + 1;
		new_symbol = new_token(NULL, NULL, PIPE, NQ);
		lst_token_add_back(data, new_symbol);
		*is_new_command = 1; // Indiquer une nouvelle commande
	}
	else
	{
		// Symbole non pris en charge
		printf("Syntax error: unknown symbol %c\n", *str);
		return (NULL);
	}
	return (ptr); // Retourner la position après le symbole
}
