/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzanchi <uzanchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:23:13 by uzanchi           #+#    #+#             */
/*   Updated: 2024/11/15 21:17:40 by uzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*Okay Ugo alors demain il faut que tu adaptes le code que tu as fait par
rapport a la liste chaine env car on a pas un char **env. Une fois que ca est
good, terminer l'expander en demandant tous le cas particulier a GPT*/
/***********************     utils    ***********************/

size_t	get_var_name_len(char *str)
{
	ssize_t	length;

	if (*(str + 1) == '?')
		return (1);
	length = -1;
	while (*str && !ft_isspace(*str))
	{
		length++;
		str++;
	}
	return (length);
}

char	*get_var_str(char *str, size_t var_exp_len, char **env)
{
	while (*env)
	{
		if (!ft_strncmp(str + 1, *env, var_exp_len) && *(*env
				+ var_exp_len) == '=')
			return (*env + var_exp_len + 1);
		env++;
	}
	return ("");
}

char	*concate_expanded_string(char **str, size_t *i, t_data *data)
{
	size_t	var_len;
	char	*first_part_str;
	char	*var_part_str;
	char	*third_part_str;
	char	*expanded_str;

	var_len = get_var_name_len(*str + *i);
	if (!var_len)
		return (NULL);
	first_part_str = ft_substr(*str, 0, *i);
// third_part_str = ft_substr(*str, *i + exp_len + 1, ft_strlen(*str) - *i - exp_len);
// Je pourrais aussi le mettre ici ce qui modifie les arguments passe
	if ((*str)[*i + 1] == '?')
		var_part_str = ft_itoa(data->exit_status);
	else
		var_part_str = ft_strdup(get_var_str(&(*str)[*i], var_len, &data->env->value));
	third_part_str = ft_substr(&(*str)[*i + var_len + 1], 0,
			ft_strlen(&(*str)[*i + var_len + 1]));
	expanded_str = ft_concate(3, first_part_str, var_part_str, third_part_str);
	if (!expanded_str)
		return (NULL);
	*i += ft_strlen(var_part_str);
	free_expanded_str(&first_part_str, &var_part_str, &third_part_str);
	return (expanded_str);
}

void	free_expanded_str(char **str1, char **str2, char **str3)
{
	free(*str1);
	*str1 = NULL;
	free(*str2);
	*str2 = NULL;
	free(*str3);
	*str3 = NULL;
}


/*     GET_VAR_NAME_LEN      \
\           MAIN            */

// int	main(void)
// {
// 	char *str = "$?42_coucou";
// 	char *str2 = "$USER_coucou";
// 	char *str3 = "$$$";
// 	char *str4 = "$$$USER";

// 	size_t len = get_var_name_len(str);
// 	size_t len2 = get_var_name_len(str2);
// 	size_t len3 = get_var_name_len(str3);
// 	size_t len4 = get_var_name_len(str4);

// 	printf("%zu\n", len);
// 	printf("%zu\n", len2);
// 	printf("%zu\n", len3);
// 	printf("%zu\n", len4);

// 	return (0);
// }


/* GET_EXPANDER_VARIABLE_STR \
\           MAIN            */

// int	main(void)
// {
//     char *str = "$USER";
//     char *str2 = "$HOME";
//     char *str3 = "$PATH";
//     char *str4 = "$SHELL";
//     char *str5 = "$NON_EXISTENT_VAR";

//     char *env[] = {
//         "USER=john_doe",
//         "HOME=/home/john_doe",
//         "PATH=/usr/bin:/bin:/usr/local/bin",
//         "SHELL=/bin/bash",
//         NULL
//     };

//     size_t len = get_var_name_len(str);
//     size_t len2 = get_var_name_len(str2);
//     size_t len3 = get_var_name_len(str3);
//     size_t len4 = get_var_name_len(str4);
//     size_t len5 = get_var_name_len(str5);

//     char *result = get_expander_variable_str(str, len, env);
//     char *result2 = get_expander_variable_str(str2, len2, env);
//     char *result3 = get_expander_variable_str(str3, len3, env);
//     char *result4 = get_expander_variable_str(str4, len4, env);
//     char *result5 = get_expander_variable_str(str5, len5, env);

//     printf("Variable %s -> Value: \"%s\"\n", str, result);
//     printf("Variable %s -> Value: \"%s\"\n", str2, result2);
//     printf("Variable %s -> Value: \"%s\"\n", str3, result3);
//     printf("Variable %s -> Value: \"%s\"\n", str4, result4);
//     printf("Variable %s -> Value: \"%s\"\n", str5, result5);

//     return (0);
// }

/*     CONCATE_EXPANDED_STRING       \
\               MAIN                */

int main(void)
{
    char *str = "Hello $USER, how are you?";
    char *str2 = "Hello $USER, how are you? $HOME";
    char *str3 = "Hello $USER, how are you? $HOME $PATH";
    char *str4 = "Hello $USER, how are you? $HOME $PATH $SHELL";
    char *str5 = "Hello $USER, how are you? $HOME $PATH $SHELL $NON_EXISTENT_VAR";

    char *env[] = {
        "USER=john_doe",
        "HOME=/home/john_doe",
        "PATH=/usr/bin:/bin:/usr/local/bin",
        "SHELL=/bin/bash",
        NULL
    };

    t_data data;
    data.env = env;

    size_t i = 0;
    char *result = concate_expanded_string(&str, &i, &data);
    i = 0;
    char *result2 = concate_expanded_string(&str2, &i, &data);
    i = 0;
    char *result3 = concate_expanded_string(&str3, &i, &data);
    i = 0;
    char *result4 = concate_expanded_string(&str4, &i, &data);
    i = 0;
    char *result5 = concate_expanded_string(&str5, &i, &data);

    printf("Expanded string: \"%s\"\n", result);
    printf("Expanded string: \"%s\"\n", result2);
    printf("Expanded string: \"%s\"\n", result3);
    printf("Expanded string: \"%s\"\n", result4);
    printf("Expanded string: \"%s\"\n", result5);

    free(result);
    free(result2);
    free(result3);
    free(result4);
    free(result5);

    return (0);
}