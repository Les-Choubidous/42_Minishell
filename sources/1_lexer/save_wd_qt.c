/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_wd_qt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:14:23 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/13 20:18:21 by uzanchi          ###   ########.fr       */
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
char	*save_word(t_data *data, char *str)
{
	char *end;
	t_token *new;

	end = str;
	while (*end && !ft_isspace(*end) && !ft_strchr(SUPPORTED_SYMBOLS, *end))
		end++;
	new = new_token(str, end, ARG, NO_QUOTES);
	if (!new)
		return (NULL);
	lst_token_add_back(data, new);
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
char	*save_quote(t_data *data, char *str, char quote_symbol)
{
	char *end_ptr;
	t_token *new;

	end_ptr = str;
	while (*end_ptr && *end_ptr != quote_symbol)
		end_ptr++;
	if (quote_symbol == '\'')
		new = new_token(str + 1, end_ptr, ARG, SPL_QUOTES);
	else
		new = new_token(str + 1, end_ptr, ARG, DBL_QUOTES);
	if (!new)
		return (NULL);
	lst_token_add_back(data, new);
	return (end_ptr + 1);
}
