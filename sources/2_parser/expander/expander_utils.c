/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:13 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/15 17:36:37 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

size_t  get_var_name_len(char *str)
{
    size_t  i;

    i = 0;
    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    return (i);
}
