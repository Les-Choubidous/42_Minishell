# include "minishell.h"

// void launch_minishell(t_data *data)
// {
//     affiche le prompt (miniishell $)
//     read line
//     renviie vers lexer
//     decompose par parser
//     execute
//     return (1 | 0)
// }

// void exit_minishell(t_data *data, int exit_status)
// {
//     ft_printf_colour(RED, "");
//     rl_clear_history(); // Le sujet dit d'avoir un working history, nous on le clean entre chaque execution
//     exit(exit_status);
// }

// int main(int ac, char **av, char **env)
// {
// 	t_data  data;

// 	if (ac != 1)
// 	{
// 		errno = EINVAL;
// 		perror("Error main");
// 		exit(EXIT_FAILURE);
// 	}
// 	ft_memset(&data, 0, sizeof(t_data));
// 	if (/*init data a fail*/)
// 		exit_minishell(&data, EXIT_FAILURE);
// 	launch_minishell(&data);
// 	return (EXIT_SUCCESS);
// }

/************************************TEST*********************************************** */

// void launch_minishell(t_data *data)
// {
//     affiche le prompt (miniishell $)
//     read line
//     renviie vers lexer
//     decompose par parser
//     execute
//     return (1 | 0)
// }

// void exit_minishell(t_data *data, int exit_status)
// {
//     ft_printf_colour(RED, "");
//     rl_clear_history(); // Le sujet dit d'avoir un working history, nous on le clean entre chaque execution
//     exit(exit_status);
// }

// # include <readline/readline.h>
// # include <readline/history.h>
// # include <sys/errno.h>
// # include <sys/stat.h>
// # include <sys/wait.h>
// # include <fcntl.h>
// # include <signal.h>

char	*f_strdup(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc((strlen(src) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
typedef struct s_prompt
{
	char	*stockage_prompt;
	struct s_prompt *next;
}			t_prompt;

void	new_node(t_prompt **head, char *input)
{
	t_prompt *new_node;
	t_prompt *temp;

	new_node = malloc(sizeof(t_prompt));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->stockage_prompt = f_strdup(input);
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}


void	free_prompt(t_prompt *head)
{
	t_prompt *temp;
	while(head)
	{
		temp = head;
		head = head->next;
		free(temp->stockage_prompt);
		free(temp);
	}
}

int main()
{
	t_prompt *data = NULL;
	//t_prompt *temp;
	char	*prompt;
	int	i = 0;

	while(i <= 3)
	{
		prompt = readline("minishell$>");
		if (prompt == NULL)
		{
			printf("\n");
			break;
		}
		if(*prompt)
		{
			add_history(prompt);
			new_node(&data, prompt);
			printf("the user write : %s\n", prompt);
			i++;
		}
		free(prompt);
	}
	printf("Commande stockee dans liste prompt : \n");
	//temp = data;
	while(data)
	{
		printf("%s\n", data->stockage_prompt);
		data = data->next;
	}

	free(data);
	return (EXIT_SUCCESS);
}
int main(int ac, char **av, char **env)
{
	char	*prompt;
	int i = 0;
	t_data	data;

	if (ac != 1)
	{
		errno = EINVAL;
		perror("Error main");
		exit(EXIT_FAILURE);
	}
	ft_memset(&data, 0, sizeof(t_data));

	if (init_data(&data, env) == EXIT_FAILURE)
		printf("error init data\n");
	t_env *current = data.env;
	while (current)
	{
		printf("KEY = [%s], VALUE = [%s]\n", current->key, current->value);
		current = current->next;
	}
	t_env *current2 = data.env;
	while (current2)
	{
		printf("KEY = [%s]\n", current2->key);
		current2 = current2->next;
	}
	while(i < 3 && av)
	{
		prompt = readline("minishell$>");
		if (prompt == NULL)
		{
			printf("\n");
			break;
		}
		if(*prompt)
		{
			add_history(prompt);
			printf("the user write : %s\n", prompt);
			i++;
		}
		free(prompt);
	}
	return (EXIT_SUCCESS);
}
