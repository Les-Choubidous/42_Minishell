#include "minishell.h"

void	print_env(t_env *print)
{
	t_env	*temp;

	temp = print;
	while (temp)
	{
		printf("KEY: %s, VALUE: %s\n", temp->key, temp->value);
		temp = temp->next;
	}
}
