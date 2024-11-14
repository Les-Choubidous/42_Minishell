/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:41:06 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/14 17:16:26 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * @brief Crée une liste chaînée des variables d'environnement.
 * 
 * La fonction parcourt le tableau `env` et, pour chaque variable d'env,
 * extrait la clé (avant le signe `=`) et la valeur (après le signe `=`).
 * Elle crée ensuite un nœud pr chaque variable et l'ajoute à 1 lst `env_list`.
 * La fonction retourne un pointeur vers le début de cette liste chaînée.
 * 
 * @param env Tableau de chaînes représentant les variables d'environnement.
 * @return Pointeur vers la liste chaînée `env_list` contenant les variables
 *         d'environnement sous forme de paires clé-valeur.
 */

t_env	*ft_get_env(char **env)
{
	t_env	*env_list;
	char	*key;
	char	*value;
	int		i;
	int		y;

	env_list = NULL;
	i = 0;
	while (env[i])
	{
		y = 0;
		while (env[i][y] && env[i][y] != '=')
			y++;
		key = ft_substr(env[i], 0, y);
		value = ft_substr(env[i], y + 1, ft_strlen(env[i]) - y - 1);
		add_env_lst(&env_list, key, value);
		i++;
	}
	//print_env(env_list);
	return (env_list);
}

/**
 * @brief Initialise la variable `full_path` avec le chemin d'accès complet.
 * 
 * Parcourt le tableau `env` pour trouver la variable d'environnement `PATH`.
 * Lorsque `PATH` est trouvée, extrait le contenu après le signe `=` et le
 * duplique dans `full_path`. Retourne un pointeur vers `full_path` ou `NULL`
 * en cas d'erreur.
 * 
 * @param env Tableau de chaînes représentant les variables d'environnement.
 * @return Pointeur vers `full_path` contenant le chemin d'accès complet, 
 *         ou `NULL` si la duplication échoue ou si `PATH` n'est pas trouvé.
 */

char	*init_full_path(char **env)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = NULL;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			full_path = ft_strdup(env[i] + 5);
			if (!full_path)
				return (NULL);
		}
		i++;
	}
	// printf("%s\n", full_path);
	return (full_path);
}

/**
 * @brief Initialise les structures d'entrée et de sortie pour `data`.
 * 
 * La fonction initialise les champs de la structure `input` et `output`
 * de `data`. `input` est configuré avec un type `INPUT`, une valeur
 * `NULL`, et un descripteur de fichier par défaut `0` (entrée standard).
 * `output` est configuré avec un type `OUTPUT`, une valeur `NULL`, et un
 * descripteur de fichier par défaut `1` (sortie standard).
 * 
 * @param data Structure contenant les champs d'entrée 
 * et de sortie à initialiser.
 */

void	init_io(t_data *data)
{
	{
		data->input.type = INPUT;
		data->input.value = NULL;
		data->input.fd = 0;
	}
	{
		data->output.type = OUTPUT;
		data->output.value = NULL;
		data->output.fd = 1;
	}
}

/**
 * @brief Ajoute un nouveau nœud à la fin de la lst des variables d'env.
 * 
 * Cette fonction crée un nouveau nœud `new_node` contenant une paire clé-valeur
 * `key` et `value` et l'ajoute à la fin de la liste chaînée `list`. 
 * Si la liste est vide, le nouveau nœud devient le 1er elmt de la liste.
 * 
 * @param list Pointeur vers le pointeur de la liste chaînée `t_env`.
 * @param key Clé de la variable d'environnement.
 * @param value Valeur de la variable d'environnement.
 */

void	add_env_lst(t_env **list, char *key, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (!*list)
		*list = new_node;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

int	init_data(t_data *data, char **env)
{
	data->full_path = init_full_path(env);
	if (!data->full_path)
		return (EXIT_FAILURE);
	data->env = ft_get_env(env);
	if (!data->env)
		return (EXIT_FAILURE);
	init_io(data);
	return (EXIT_SUCCESS);
}
