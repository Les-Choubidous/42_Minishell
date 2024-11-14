#include "minishell.h"

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