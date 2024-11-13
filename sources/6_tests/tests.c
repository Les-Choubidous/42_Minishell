#include "minishell.h"

void	print_env(t_env *print)
{
	t_env	*temp;

	temp = print;
	while (temp)
	{
		printf("%s\n", temp->value);
		temp = temp->next;
	}
}
