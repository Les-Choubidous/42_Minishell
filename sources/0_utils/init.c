/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melinamotylewski <melinamotylewski@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:41:06 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/13 15:58:08 by melinamotyl      ###   ########.fr       */
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

t_env *create_node(const char *env_part)
{
	t_env	*new_node;
	char	*equal_pos;
	size_t	key_len;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return NULL;

	equal_pos = ft_strchr(env_part, '=');
	if (!equal_pos)
	{
		free(new_node);
		return (NULL);
	}
	key_len = equal_pos - env_part;

	new_node ->key = ft_substr(env_part, 0, key_len);

	new_node->value = ft_strdup(equal_pos + 1);
	if (!new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

t_env *ft_get_env(char **env)
{
	t_env *env_list = NULL;
	t_env *new_node = NULL;
	t_env *last_node = NULL;
	int i = 0;

	while (env[i])
	{
		new_node = create_node(env[i]);
		if (!new_node)
		{
			free_env_list(env_list);
			return (NULL);
		}
		if (env_list)
			env_list = new_node;
		else
			last_node->next = new_node;
		last_node = new_node;
		i++;
	}
	return env_list;
}
void	free_env_list(t_env *env_list)
{
	t_env	*temp;
	while(env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->key);
		free(temp->value);
		free(temp);
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
