/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:12:51 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/13 19:34:13 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

# define UNEXPECTED_PIPE "Syntax error: unexpected token '|' in argument\n"
# define UNCLOSED_QUOTE "Syntax error: unclosed quote in argument\n"

/***********************     SAVE SYMBOLS     ********************************/

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
	t_type type;
	t_quote quote;
	char *start;
	char *end;

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
	while (*end && !ft_isspace(*end) && !ft_strchr(SUPPORTED_SYMBOLS, *end) &&
		!((quote == SPL_QUOTES && *end == '\'') || (quote == DBL_QUOTES && *end == '\"')))
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
char	*save_symbol(t_data *data, char *str)
{
	t_token *new;
	char *ptr;

	if (check_symbol_at_end_of_string(str) || check_double_tokens(str))
		return (NULL);
	if (*str == '<' || *str == '>')
		ptr = redirection_helper(str, &new);
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

/***********************     LEXER UTILS     *********************************/

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

/***********************     LEXER MAIN      *********************************/

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
