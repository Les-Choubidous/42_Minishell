/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: memotyle <memotyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:41:06 by memotyle          #+#    #+#             */
/*   Updated: 2024/11/12 17:15:01 by memotyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
			break ;
		}
		i++;
	}
	return (full_path);
}

#include <stdlib.h>
#include <string.h>

t_env	*add_env_node(t_env **head, char *env_var)
{
	t_env	*new_node;
	t_env	*temp;
	char	*equal;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal = strchr(env_var, '=');
	if (!equal)
		return (free(new_node), NULL);
	new_node->key = strndup(env_var, equal - env_var);
	if (!new_node->key)
		return (free(new_node), NULL);
	new_node->value = strdup(equal + 1);
	if (!new_node->value)
		return (free(new_node->key), free(new_node), NULL);
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	return (new_node);
}


t_env	*get_env(char **env)
{
	t_env	*environnement = NULL;
	int		i = 0;

	while (env[i])
	{
		if (!add_env_node(&environnement, env[i]))
		{
			t_env *temp;
			while (environnement)
			{
				temp = environnement;
				environnement = environnement->next;
				free(temp->value);
				free(temp);
			}
			return (NULL);
		}
		i++;
	}
	return (environnement);
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
int	init_data(t_data *data, char **env)
{
	data->full_path = init_full_path(env);
	if (!data->full_path)
		return (EXIT_FAILURE);

	data->env = get_env(env);
	if (!data->env)
		return (EXIT_FAILURE);
	init_io(data);
	return (EXIT_SUCCESS);
}
