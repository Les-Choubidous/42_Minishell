/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_wd_qt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:14:23 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/15 15:01:34 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Sauvegarde un mot (séquence sans espaces ni symboles) en tant
 * que token.
 *
 * Parcourt la chaîne jusqu'à un espace ou un symbole et crée un token pour
 * le mot trouvé, en l'ajoutant à la liste des tokens.
 *
 * @param data Structure principale contenant la liste de tokens.
 * @param str Chaîne à analyser.
 * @return Pointeur après le mot dans la chaîne.
 */
char	*save_word(t_data *data, char *str, int *is_new_command)
{
	char	*end;
	t_token	*new;
	t_type	type;

	end = str;
	while (*end && !ft_isspace(*end) && !ft_strchr(SUPPORTED_SYMBOLS, *end))
		end++;
	if (*is_new_command)
		type = CMD;
	else
		type = ARG;
	new = new_token(str, end, type, NQ);
	if (!new)
		return (NULL);
	lst_token_add_back(data, new);
	is_new_command = 0;
	return (end);
}

/**
 * @brief Sauvegarde une chaîne entre guillemets en tant que token.
 *
 * Identifie la fin de la citation (simple ou double), crée un token pour le
 * texte entre guillemets et l'ajoute à la liste de tokens.
 *
 * @param data Structure principale contenant la liste de tokens.
 * @param str Chaîne à analyser.
 * @param quote_symbol Caractère de guillemet (simple ou double).
 * @return Pointeur après la fin de la citation.
 */
char	*save_quote(t_data *data, char *str, int *is_new_command)
{
	char	quote_symbol;
	char	*end_ptr;
	t_token	*new;
	t_type	type;
	t_quote	quote_type;

	quote_symbol = *str;
	str++; // Passe le guillemet ouvrant
	end_ptr = str;
	printf("str : %s\n", str);
	while (*end_ptr && *end_ptr != quote_symbol)
		end_ptr++;
	printf("en ptr : %s\n", end_ptr);
	if (!*end_ptr)
	{
		printf("Syntax error: unclosed quote\n");
		return (NULL);
	}
	// Détermination du type de quote
	if (quote_symbol == '\'')
		quote_type = SQ;
	else
		quote_type = DQ;
	// Détermination du type de token
	if (*is_new_command)
		type = CMD;
	else
		type = ARG;
	new = new_token(str, end_ptr, type, quote_type);
	if (!new)
		return (NULL);
	lst_token_add_back(data, new);
	*is_new_command = 0;  // Mise à jour de is_new_command
	return (end_ptr + 1); // Passe le guillemet fermant
}
