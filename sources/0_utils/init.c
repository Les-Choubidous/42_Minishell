/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:41:06 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/13 18:36:56 by melinamotyl      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_full_path(char **env)
{
	int		i;
	char	*full_path;

	i = 0;
	full_path = NULL;
	while(env[i])
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

void	init_io(t_data *data)
{
	{
		data->input.type = STDIN;
		data->input.value = NULL;
		data->input.fd = 0;
	}
	{
		data->output.type = STDOUT;
		data->output.value = NULL;
		data->output.fd = 1;
	}
}

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

void free_env_list(t_env *list)
{
	t_env *temp;

	while (list)
	{
		temp = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = temp;
	}
}

t_env *ft_get_env(char **env)
{
	t_env	*env_list = NULL;
	char	*key;
	char	*value;
	int		i;
	int		y;

	i = 0;
	while (env[i])
	{
		y = 0;
		while(env[i][y] && env[i][y] != '=')
			y++;
		key = ft_substr(env[i], 0, y);
		value = ft_substr(env[i], y + 1, ft_strlen(env[y]));
		// if (!key || !value)
		// {
		// 	free(key);
		// 	free(value);
		// 	return (NULL);
		// }
		add_env_lst(&env_list, key, value);
		i++;
	}
	//free_env_list(env_list);
	print_env(env_list);
	return (env_list);
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
