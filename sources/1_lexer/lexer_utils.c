/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:14:43 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/15 16:01:06 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Vérifie si un symbole de redirection est en fin de chaîne.
 * 
 * Affiche une erreur de syntaxe si un symbole de redirection est suivi de
 * rien.
 * 
 * @param str Chaîne à analyser.
 * @return `EXIT_FAILURE` en cas d'erreur, `EXIT_SUCCESS` sinon.
 */
int	check_symbol_at_end_of_string(char *str)
{
	if ((*str == '<' || *str == '>') && *str == *str + 1 && !*(str + 2))
	{
		printf("Syntax error: excepted token after %c%c symbol\n", *str, *str);
		return (EXIT_FAILURE);
	}
	if (!*str + 1)
	{
		printf("Syntax error: excepted token after %c symbol\n", *str);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Vérifie la validité des symboles consécutifs.
 * 
 * Vérifie si des symboles de redirection sont placés de manière correcte,
 * retourne une erreur en cas de séquence invalide.
 * 
 * @param str Chaîne à analyser.
 * @return `EXIT_FAILURE` en cas d'erreur, `EXIT_SUCCESS` sinon.
 */
int	check_double_tokens(char *str)
{
	if (!ft_strchr(SUPPORTED_SYMBOLS, *(str + 1)))
		return (EXIT_SUCCESS);
	else
	{
		if ((*str == '<' && *(str + 1) == '<') || (*str == '>' && *(str + 1) == '>'))
			return (EXIT_SUCCESS);
		else
		{
			printf("Syntax error: unexpected token %c after token %c\n",
				*str + 1, *str);
			return (EXIT_FAILURE);
		}
	}
}

/**
 * @brief Crée un nouveau token pour l'analyse lexicale.
 * 
 * Alloue un nouveau `t_token`, copie la valeur entre `start` et `end`,
 * et initialise le type et le type de guillemet. Retourne le token créé
 * ou `NULL` en cas d'échec.
 * 
 * @param start Début de la valeur dans la chaîne.
 * @param end Fin de la valeur dans la chaîne.
 * @param type Type de token (ex: ARG, PIPE, etc.).
 * @param quote Type de guillemet (simple, double, ou aucun).
 * @return Pointeur vers le nouveau token ou `NULL` en cas d'erreur.
 */
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

/**
 * @brief Ajoute un token à la fin de la liste chaînée des tokens.
 * 
 * Traverse la liste de tokens dans `data` et ajoute `new` à la fin.
 * 
 * @param data Structure principale contenant la liste de tokens.
 * @param new Token à ajouter.
 */
void	lst_token_add_back(t_data *data, t_token *new)
{
	t_token *tmp;

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
