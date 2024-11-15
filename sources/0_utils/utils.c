/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:02:24 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/14 18:39:03 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_printf_exit_code(char *str, int exit_code)
{
	printf("%s", str);
	return (exit_code);
}

void	print_env(t_env *list)
{
	while (list)
	{
		printf("\tKEY : %s\nVALUE :  %s\n\n", list->key, list->value);
		list = list->next;
	}
}


